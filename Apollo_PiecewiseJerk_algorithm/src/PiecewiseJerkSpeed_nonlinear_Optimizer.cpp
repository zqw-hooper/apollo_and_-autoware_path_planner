#define HAVE_CSTDDEF
#include <coin/IpIpoptApplication.hpp>
#include <coin/IpSolveStatistics.hpp>
#undef HAVE_CSTDDEF

#include <chrono>
#include <iostream>
#include <fstream>

#include "glog/logging.h"
#include "PiecewiseJerkSpeed_nonlinear_Optimizer.hpp"
#include "PiecewiseJerkSpeedProblem.hpp"
#include "PiecewiseJerkPathProblem.hpp"
#include "PiecewiseJerkSpeedNonlinearIpoptInterface.hpp"
#include "SpeedData.hpp"
#include "SpeedProfileGenerator.hpp"

PiecewiseJerkSpeedNonlinearOptimizer::PiecewiseJerkSpeedNonlinearOptimizer()
    : smoothed_speed_limit_(0, 0, 0),
      smoothed_path_curvature_(0, 0, 0) {}
bool PiecewiseJerkSpeedNonlinearOptimizer::Process(std::vector<std::pair<double, double>> &s_bounds,
                                                   const std::vector<std::pair<double, double>> &soft_s_bounds,
                                                   const std::vector<double> &ref_s_list,
                                                   const SpeedLimit &speed_limit,
                                                   double dt,
                                                   const DiscretizedPath &path,
                                                   double init_v,
                                                   double init_a,
                                                   SpeedData *speed_data,
                                                   double reference_crusie_velocity)
{
    if (s_bounds.size() != soft_s_bounds.size())
    {
        return false;
    }
    delta_t_ = dt;                                // 时间间隔，这里等于0.2s
    num_of_knots_ = s_bounds.size();              // 优化的点数目，这里等于40
    total_time_ = delta_t_ * (num_of_knots_ - 1); // 总时间
    total_length_ = path.back().s_;               //总长度
    if (fabs(total_length_) < 1e-7)
    {
        LOG(ERROR) << "Path length is 0!";
        return false;
    }
    // 初始状态
    s_init_ = 0;
    s_dot_init_ = init_v;
    s_ddot_init_ = init_a;
    // TODO: use config.
    s_dot_max_ = std::max(15.0, s_dot_init_);
    s_ddot_max_ = 2;
    s_ddot_min_ = -3;
    s_dddot_min_ = -4;
    s_dddot_max_ = 2;

    // s的上边界
    for (auto &bound : s_bounds)
    {
        bound.second = std::min(bound.second, total_length_);
    }

    // 优化 reference_line
    std::vector<double> distance;
    std::vector<double> velocity;
    std::vector<double> acceleration;
    const auto qp_start = std::chrono::system_clock::now();
    // 根据 s_bounds,优化reference_line
    const auto qp_smooth_status =
        OptimizeByQP(s_bounds, ref_s_list, &distance, &velocity, &acceleration);
    const auto qp_end = std::chrono::system_clock::now();
    std::chrono::duration<double> qp_diff = qp_end - qp_start;
    std::cout << "speed qp optimization takes " << qp_diff.count() * 1000.0 << " ms" << std::endl;
    if (!qp_smooth_status)
    {
        return false;
    }
    // reference_line
    // 横坐标t, 纵坐标s
    std::ofstream out;
    out.open("../plot/ref.csv");
    out << "t,ref,optimized_ref,s_bounds_lower,s_bounds_upper,velocity" << std::endl;
    for (int i = 0; i != ref_s_list.size(); ++i)
    {

        out << i * dt << "," << ref_s_list[i] << "," << distance[i] << ","
            << s_bounds[i].first << "," << s_bounds[i].second
            << "," << velocity[i] << std::endl;
    }
    out.close();

    // Smooth curvature
    const auto curvature_smooth_start = std::chrono::system_clock::now();
    // using piecewise_jerk_path to fit a curve of path kappa profile
    const auto path_curvature_smooth_status = SmoothPathCurvature(path);
    const auto curvature_smooth_end = std::chrono::system_clock::now();
    std::chrono::duration<double> curvature_smooth_diff =
        curvature_smooth_end - curvature_smooth_start;
    std::cout << "path curvature smoothing for nlp optimization takes "
              << curvature_smooth_diff.count() * 1000.0 << " ms" << std::endl;
    if (!path_curvature_smooth_status)
        return false;

    // Smooth speed limit.
    const auto speed_limit_smooth_start = std::chrono::system_clock::now();
    const auto speed_limit_smooth_status = SmoothSpeedLimit(speed_limit);
    const auto speed_limit_smooth_end = std::chrono::system_clock::now();
    std::chrono::duration<double> speed_limit_smooth_diff =
        speed_limit_smooth_end - speed_limit_smooth_start;
    std::cout << "speed limit smoothing for nlp optimization takes "
              << speed_limit_smooth_diff.count() * 1000.0 << " ms" << std::endl;
    if (!speed_limit_smooth_status)
        return false;

    // Solve.
    const auto nlp_start = std::chrono::system_clock::now();
    // 速度规划  // trajectory
    const auto nlp_smooth_status =
        speed_non_linear_optimizer(s_bounds, soft_s_bounds, &distance, &velocity, &acceleration, reference_crusie_velocity);
    const auto nlp_end = std::chrono::system_clock::now();
    std::chrono::duration<double> nlp_diff = nlp_end - nlp_start;
    LOG(INFO) << "speed nlp optimization takes " << nlp_diff.count() * 1000.0
              << " ms";

    speed_data->clear();
    if (!nlp_smooth_status)
    {
        return false;
    }

    // 返回计算出的 speed_data
    speed_data->AppendSpeedPoint(distance[0], 0.0, velocity[0], acceleration[0],
                                 0.0);
    for (int i = 1; i < num_of_knots_; ++i)
    {
        // Avoid the very last points when already stopped
        if (velocity[i] < 0.0)
        {
            break;
        }
        speed_data->AppendSpeedPoint(
            distance[i], delta_t_ * i, velocity[i], acceleration[i],
            (acceleration[i] - acceleration[i - 1]) / delta_t_);
    }

    // In case time is too short.
    SpeedProfileGenerator::FillEnoughSpeedPoints(speed_data);
    return true;
}

bool PiecewiseJerkSpeedNonlinearOptimizer::OptimizeByQP(const std::vector<std::pair<double, double>> &s_bounds,
                                                        const std::vector<double> &ref_s_list,
                                                        std::vector<double> *distance,
                                                        std::vector<double> *velocity,
                                                        std::vector<double> *acceleration)
{
    // 初始状态
    std::array<double, 3> init_states = {0, s_dot_init_, s_ddot_init_};
    // std::array<double, 3> init_states = {30, 0, 0};
    // std::cout << "s_init_   " << s_init_ << std::endl;
    PiecewiseJerkSpeedProblem piecewise_jerk_speed_problem(num_of_knots_, delta_t_,
                                                           init_states);
    std::cout << "num_of_knots_  " << num_of_knots_ << std::endl;
    piecewise_jerk_speed_problem.set_dx_bounds(
        0.0, s_dot_max_);
    piecewise_jerk_speed_problem.set_ddx_bounds(s_ddot_min_, s_ddot_max_);
    piecewise_jerk_speed_problem.set_dddx_bound(s_dddot_min_, s_dddot_max_);
    piecewise_jerk_speed_problem.set_x_bounds(s_bounds);
    piecewise_jerk_speed_problem.set_weight_x(10.0);
    piecewise_jerk_speed_problem.set_weight_dx(0.0);
    piecewise_jerk_speed_problem.set_weight_ddx(1.0);
    piecewise_jerk_speed_problem.set_weight_dddx(1.0);
    piecewise_jerk_speed_problem.set_x_ref(10.0, ref_s_list);
    // Solve the problem
    if (!piecewise_jerk_speed_problem.Optimize())
    {
        std::cout << "Speed Optimization by Quadratic Programming failed" << std::endl;
        return false;
    }
    *distance = piecewise_jerk_speed_problem.opt_x();
    *velocity = piecewise_jerk_speed_problem.opt_dx();
    *acceleration = piecewise_jerk_speed_problem.opt_ddx();
    return true;
}

bool PiecewiseJerkSpeedNonlinearOptimizer::SmoothPathCurvature(const DiscretizedPath &cartesian_path)
{
    const double delta_s = 0.5;
    std::vector<double> path_curvature;
    for (double path_s = cartesian_path.front().s_;
         path_s < cartesian_path.back().s_ + delta_s; path_s += delta_s)
    {
        const auto &path_point = cartesian_path.Evaluate(path_s);
        path_curvature.push_back(path_point.kappa_);
    }
    const auto &path_init_point = cartesian_path.front();
    std::array<double, 3> init_state = {path_init_point.kappa_,
                                        path_init_point.dkappa_,
                                        path_init_point.ddkappa_};
    PiecewiseJerkPathProblem piecewise_jerk_problem(path_curvature.size(),
                                                    delta_s, init_state);
    piecewise_jerk_problem.set_x_bounds(-1.0, 1.0);
    piecewise_jerk_problem.set_dx_bounds(-10.0, 10.0);
    piecewise_jerk_problem.set_ddx_bounds(-10.0, 10.0);
    piecewise_jerk_problem.set_dddx_bound(-10.0, 10.0);

    piecewise_jerk_problem.set_weight_x(0.0);
    piecewise_jerk_problem.set_weight_dx(10.0);
    piecewise_jerk_problem.set_weight_ddx(10.0);
    piecewise_jerk_problem.set_weight_dddx(10.0);

    piecewise_jerk_problem.set_x_ref(10.0, path_curvature);

    if (!piecewise_jerk_problem.Optimize(1000))
    {
        std::string msg("Smoothing path curvature failed");
        LOG(WARNING) << msg;
        return false;
    }

    std::vector<double> opt_x;
    std::vector<double> opt_dx;
    std::vector<double> opt_ddx;

    opt_x = piecewise_jerk_problem.opt_x();
    opt_dx = piecewise_jerk_problem.opt_dx();
    opt_ddx = piecewise_jerk_problem.opt_ddx();

    PiecewiseJerkTrajectory1d smoothed_path_curvature(
        opt_x.front(), opt_dx.front(), opt_ddx.front());
    for (size_t i = 1; i < opt_ddx.size(); ++i)
    {
        double j = (opt_ddx[i] - opt_ddx[i - 1]) / delta_s;
        smoothed_path_curvature.AppendSegment(j, delta_s);
    }
    smoothed_path_curvature_ = smoothed_path_curvature;
    return true;
}

bool PiecewiseJerkSpeedNonlinearOptimizer::SmoothSpeedLimit(const SpeedLimit &speed_limit)
{
    double delta_s = 2.0;
    std::vector<double> speed_ref;
    for (int i = 0; i < 100; ++i)
    {
        double path_s = i * delta_s;
        double limit = speed_limit.GetSpeedLimitByS(path_s);
        speed_ref.emplace_back(limit);
    }
    std::array<double, 3> init_state = {speed_ref[0], 0.0, 0.0};
    PiecewiseJerkPathProblem piecewise_jerk_problem(speed_ref.size(), delta_s,
                                                    init_state);
    piecewise_jerk_problem.set_x_bounds(0.0, 50.0);
    piecewise_jerk_problem.set_dx_bounds(-10.0, 10.0);
    piecewise_jerk_problem.set_ddx_bounds(-10.0, 10.0);
    piecewise_jerk_problem.set_dddx_bound(-10.0, 10.0);

    piecewise_jerk_problem.set_weight_x(0.0);
    piecewise_jerk_problem.set_weight_dx(10.0);
    piecewise_jerk_problem.set_weight_ddx(10.0);
    piecewise_jerk_problem.set_weight_dddx(10.0);

    piecewise_jerk_problem.set_x_ref(10.0, speed_ref);

    if (!piecewise_jerk_problem.Optimize(4000))
    {
        std::string msg("Smoothing speed limit failed");
        LOG(WARNING) << msg;
        return false;
    }

    std::vector<double> opt_x;
    std::vector<double> opt_dx;
    std::vector<double> opt_ddx;

    opt_x = piecewise_jerk_problem.opt_x();
    opt_dx = piecewise_jerk_problem.opt_dx();
    opt_ddx = piecewise_jerk_problem.opt_ddx();
    PiecewiseJerkTrajectory1d smoothed_speed_limit(opt_x.front(), opt_dx.front(),
                                                   opt_ddx.front());

    for (size_t i = 1; i < opt_ddx.size(); ++i)
    {
        double j = (opt_ddx[i] - opt_ddx[i - 1]) / delta_s;
        smoothed_speed_limit.AppendSegment(j, delta_s);
    }

    smoothed_speed_limit_ = smoothed_speed_limit;

    return true;
}

bool PiecewiseJerkSpeedNonlinearOptimizer::speed_non_linear_optimizer(const std::vector<std::pair<double, double>> &s_bounds,
                                                                      const std::vector<std::pair<double, double>> &soft_s_bounds,
                                                                      std::vector<double> *distance,
                                                                      std::vector<double> *velocity,
                                                                      std::vector<double> *acceleration,
                                                                      double reference_cruise_velocity)
{
    // Set optimizer instance
    // 纵向速度,加速度,加加速度的最大,最小值
    auto ptr_interface = new PiecewiseJerkSpeedNonlinearIpoptInterface(
        s_init_, s_dot_init_, s_ddot_init_, delta_t_, num_of_knots_,
        total_length_, s_dot_max_, s_ddot_min_, s_ddot_max_, s_dddot_min_,
        s_dddot_max_);

    // s点上,下边界  // size = 41
    std::cout << "s_bounds.size()   " << s_bounds.size() << std::endl;
    ptr_interface->set_safety_bounds(s_bounds);
    ptr_interface->set_curvature_curve(smoothed_path_curvature_);
    // 纵向的速度边界
    ptr_interface->set_speed_limit_curve(smoothed_speed_limit_);

    // Warm start // 使用 smooth_driving_guide_line
    const auto &warm_start_distance = *distance;
    const auto &warm_start_velocity = *velocity;
    const auto &warm_start_acceleration = *acceleration;
    if (warm_start_distance.empty() || warm_start_velocity.empty() ||
        warm_start_acceleration.empty() ||
        warm_start_distance.size() != warm_start_velocity.size() ||
        warm_start_velocity.size() != warm_start_acceleration.size())
    {
        std::string msg(
            "Piecewise jerk speed nonlinear optimizer warm start invalid!");
        LOG(WARNING) << msg;
        return false;
    }

    std::vector<std::vector<double>> warm_start;
    std::size_t size = warm_start_distance.size();
    for (std::size_t i = 0; i < size; ++i)
    {
        warm_start.emplace_back(std::initializer_list<double>(
            {warm_start_distance[i], warm_start_velocity[i],
             warm_start_acceleration[i]}));
    }
    ptr_interface->set_warm_start(warm_start);

    // ptr_interface->set_soft_safety_bounds(s_soft_bounds_);
    // ptr_interface->set_w_soft_s_bound(config.soft_s_bound_weight());

    // 优化函数的设置
    // 参考论文:
    // << Optimal Trajectory Generation for Autonomous Vehicle Under Centripetal Acceleration 
    // Constraints for In-lane Driving Scenarios >>
    // term (1)(2)(3)
    ptr_interface->set_w_overall_a(2.0);                  //acc_weight
    ptr_interface->set_w_overall_j(3.0);                  //jerk_weight
    ptr_interface->set_w_overall_centripetal_acc(1000.0); // lat_acc_weight

    // Set weights and reference values
    // Use smoothed reference // smooth_driving_guide_line
    // FLAGS_use_smoothed_dp_guide_line
    // term (5)
    ptr_interface->set_reference_spatial_distance(*distance);
    // s_potential_weight  // 带w的是权重
    ptr_interface->set_w_reference_spatial_distance(10.0);
    // In apollo, default cruise speed is 5.0.
    // term(6)
    ptr_interface->set_reference_speed(5.0);   // cruise_speed_
    ptr_interface->set_w_reference_speed(5.0); // ref_v_weight

    Ipopt::SmartPtr<Ipopt::TNLP> problem = ptr_interface;
    Ipopt::SmartPtr<Ipopt::IpoptApplication> app = IpoptApplicationFactory();

    app->Options()->SetIntegerValue("print_level", 0);
    app->Options()->SetIntegerValue("max_iter", 1000);

    Ipopt::ApplicationReturnStatus status = app->Initialize();
    if (status != Ipopt::Solve_Succeeded)
    {
        std::string msg(
            "Piecewise jerk speed nonlinear optimizer failed during "
            "initialization!");
        LOG(WARNING) << msg;
        return false;
    }

    const auto start_timestamp = std::chrono::system_clock::now();
    /** Solve a problem that inherits from TNLP */
    status = app->OptimizeTNLP(problem);
    const auto end_timestamp = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end_timestamp - start_timestamp;
    LOG(INFO) << "The optimization problem take time: " << diff.count() * 1000.0
              << " ms.";
    if (status == Ipopt::Solve_Succeeded ||
        status == Ipopt::Solved_To_Acceptable_Level)
    {
        // Retrieve some statistics about the solve
        Ipopt::Index iter_count = app->Statistics()->IterationCount();
        DLOG(INFO) << "The problem solved in " << iter_count << " iterations!";
        Ipopt::Number final_obj = app->Statistics()->FinalObjective();
        DLOG(INFO) << " The final value of the objective function is " << final_obj
                   << '.';
    }
    else
    {
        std::string msg("Piecewise jerk speed nonlinear optimizer failed!");
        LOG(WARNING) << msg;
        return false;
    }
    ptr_interface->get_optimization_results(distance, velocity, acceleration);
    return true;
}