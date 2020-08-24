#include "osqp_problem.h"

namespace
{
  constexpr double kMaxVarRange = 1.0e10;
}

// 构造函数
OSQPProblem::OSQPProblem(const size_t num_of_knots, const double delta_s,
                         const std::array<double, 3> &x_init)
{
  if (num_of_knots < 2)
  {
    std::cout << "Error when init problem." << std::endl;
    return;
  }
  // 路径点的数目
  num_of_knots_ = num_of_knots;
  x_init_ = x_init;
  delta_s_ = delta_s;
  // 边界对的数目
  x_bounds_.resize(num_of_knots_, std::make_pair(-kMaxVarRange, kMaxVarRange));
  dx_bounds_.resize(num_of_knots_, std::make_pair(-kMaxVarRange, kMaxVarRange));
  ddx_bounds_.resize(num_of_knots_,
                     std::make_pair(-kMaxVarRange, kMaxVarRange));
}

// osqp内部的核函数矩阵,计算P
void OSQPProblem::CalculateKernel(std::vector<c_float> *P_data,
                                  std::vector<c_int> *P_indices,
                                  std::vector<c_int> *P_indptr)
{
  // if num_of_knots_=2;
  // x for example: [x_0,x_0',x_0'',x_1,x_1',x_1'']^T
  const int n = static_cast<int>(num_of_knots_);
  const int num_of_variables = 3 * n;
  const int num_of_nonzeros = num_of_variables + (n - 1);

  std::cout << "num_of_knots_   " << num_of_knots_ << std::endl;
  std::cout << "num_of_nonzeros   " << num_of_nonzeros << std::endl;

  // std::pair<c_int, c_float>>: c_int表示元素的索引   c_float表示
  std::vector<std::vector<std::pair<c_int, c_float>>> columns(num_of_variables);
  int value_index = 0;

  // 上述设置了目标函数，主要包括：
  // l^2+l'^2+l''^2，以及l'''^2，其中l'''通过l''前后两帧之差与delta_s之比替代

  // x(i)^2 * (w_x + w_x_ref)
  // std::array<double, 3> scale_factor_ = {{1.0, 1.0, 1.0}};
  // colum 0 到 (n-2)
  for (int i = 0; i < n - 1; ++i)
  {
    columns[i].emplace_back(
        i, (weight_x_ + weight_x_ref_) / (scale_factor_[0] * scale_factor_[0]));
    ++value_index;
    // std::cout << "(weight_x_ + weight_x_ref_) / (scale_factor_[0] * scale_factor_[0])    " << (weight_x_ + weight_x_ref_) / (scale_factor_[0] * scale_factor_[0]) << std::endl;
  }

  // colum (n-1)
  // x(n-1)^2 * (w_x + w_x_ref + w_end_x)
  columns[n - 1].emplace_back(
      n - 1, (weight_x_ + weight_x_ref_ + weight_end_state_[0]) /
                 (scale_factor_[0] * scale_factor_[0]));
  ++value_index;
  // std::cout << "(weight_x_ + weight_x_ref_ + weight_end_state_[0]) / (scale_factor_[0] * scale_factor_[0])    "
  //           << ((weight_x_ + weight_x_ref_ + weight_end_state_[0]) / (scale_factor_[0] * scale_factor_[0])) << std::endl;

  // x(i)'^2 * w_dx
  //
  for (int i = 0; i < n - 1; ++i)
  {
    columns[n + i].emplace_back(
        n + i, weight_dx_ / (scale_factor_[1] * scale_factor_[1]));
    ++value_index;
  }
  // std::cout << "weight_dx_ / (scale_factor_[1] * scale_factor_[1])    " << weight_dx_ / (scale_factor_[1] * scale_factor_[1]) << std::endl;

  // x(n-1)'^2 * (w_dx + w_end_dx)
  columns[2 * n - 1].emplace_back(2 * n - 1,
                                  (weight_dx_ + weight_end_state_[1]) /
                                      (scale_factor_[1] * scale_factor_[1]));
  ++value_index;
  // std::cout << "(weight_dx_ + weight_end_state_[1]) /  (scale_factor_[1] * scale_factor_[1])    " << (weight_dx_ + weight_end_state_[1]) / (scale_factor_[1] * scale_factor_[1]) << std::endl;

  auto delta_s_square = delta_s_ * delta_s_;

  // x(i)''^2 * (w_ddx + 2 * w_dddx / delta_s^2)
  columns[2 * n].emplace_back(2 * n,
                              (weight_ddx_ + weight_dddx_ / delta_s_square) /
                                  (scale_factor_[2] * scale_factor_[2]));
  ++value_index;
  // std::cout << "(weight_dx_ + weight_end_state_[1]) /  (scale_factor_[1] * scale_factor_[1])    " << (weight_dx_ + weight_end_state_[1]) / (scale_factor_[1] * scale_factor_[1]) << std::endl;

  for (int i = 1; i < n - 1; ++i)
  {
    columns[2 * n + i].emplace_back(
        2 * n + i, (weight_ddx_ + 2.0 * weight_dddx_ / delta_s_square) /
                       (scale_factor_[2] * scale_factor_[2]));
    ++value_index;
  }
  // std::cout << "(weight_dx_ + weight_end_state_[1]) /  (scale_factor_[1] * scale_factor_[1])    " << (weight_dx_ + weight_end_state_[1]) / (scale_factor_[1] * scale_factor_[1]) << std::endl;

  columns[3 * n - 1].emplace_back(
      3 * n - 1,
      (weight_ddx_ + 1.0 * weight_dddx_ / delta_s_square + weight_end_state_[2]) /
          (scale_factor_[2] * scale_factor_[2]));
  ++value_index;

  // -2 * w_dddx / delta_s^2 * x(i)'' * x(i + 1)''
  for (int i = 1; i < n; ++i)
  {
    columns[2 * n + i].emplace_back(2 * n + i - 1,
                                    (-1.0 * weight_dddx_ / delta_s_square) /
                                        (scale_factor_[2] * scale_factor_[2]));
    ++value_index;
  }

  if (value_index != num_of_nonzeros)
  {
    std::cout << "Error in calculate kernel!" << std::endl;
  }

  // P_indptr: 每列不为0的元素的数目
  int ind_p = 0;
  for (int i = 0; i < num_of_variables; ++i)
  {
    P_indptr->push_back(ind_p);
    for (const auto &row_data_pair : columns[i])
    {
      // P_data: 每列不为0的元素的数值
      P_data->push_back(row_data_pair.second * 1.0);
      // P_indices: 每列不为0的元素的索引
      P_indices->push_back(row_data_pair.first);
      // 不为0的元素的数目加1
      ++ind_p;
    }
  }
  P_indptr->push_back(ind_p);
}

//  osqp内部的核函数矩阵,计算A   // 计算A和上下边界 //  仿射约束
void OSQPProblem::CalculateAffineConstraint(
    std::vector<c_float> *A_data, std::vector<c_int> *A_indices,
    std::vector<c_int> *A_indptr, std::vector<c_float> *lower_bounds,
    std::vector<c_float> *upper_bounds)
{ // if num_of_knots_=2;
  // x for example: [x_0,x_0',x_0'',x_1,x_1',x_1'']^T

  // 3N params bounds on x, x', x''
  // which are
  // 3(N-1) constraints on x, x', x''
  // 3 constraints on x_init_

  //说的很详细，主要包含 变量边界约束，
  // 三个运动学公式约束以及初始状态约束，边界约束主要是横向最大位移、最大速度、最大加速度等，
  // 运动学公式主要是 x(i->i+1)''' = (x(i+1)'' - x(i)'') / delta_s等等，

  const int n = static_cast<int>(num_of_knots_);
  const int num_of_variables = 3 * n;
  const int num_of_constraints = num_of_variables + 3 * (n - 1) + 3;
  lower_bounds->resize(num_of_constraints);
  upper_bounds->resize(num_of_constraints);

  std::vector<std::vector<std::pair<c_int, c_float>>> variables(
      num_of_variables);

  int constraint_index = 0;

  // std::cout << "num_of_variables   " << num_of_variables << std::endl;

  // 首先是变量约束，通过赋值变量上下边界，完成约束设置首先是变量约束，通过赋值变量上下边界，完成约束设置
  // set x, x', x'' bounds
  // x:[0,n)  x':[n,2n)   x":[2n,3n)   // 对应的索引
  // 位置,速度,加速度  //一共 3*num_of_knots_ 个
  for (int i = 0; i < num_of_variables; ++i)
  {
    if (i < n)
    { // 位置  // num_of_knots_个
      variables[i].emplace_back(constraint_index, 1.0);
      lower_bounds->at(constraint_index) =
          x_bounds_[i].first * scale_factor_[0];
      upper_bounds->at(constraint_index) =
          x_bounds_[i].second * scale_factor_[0];
    }
    else if (i < 2 * n)
    { // 速度  // num_of_knots_个
      variables[i].emplace_back(constraint_index, 1.0);
      lower_bounds->at(constraint_index) =
          dx_bounds_[i - n].first * scale_factor_[1];
      upper_bounds->at(constraint_index) =
          dx_bounds_[i - n].second * scale_factor_[1];
    }
    else
    { // 加速度  // num_of_knots_个
      variables[i].emplace_back(constraint_index, 1.0);
      lower_bounds->at(constraint_index) =
          ddx_bounds_[i - 2 * n].first * scale_factor_[2];
      upper_bounds->at(constraint_index) =
          ddx_bounds_[i - 2 * n].second * scale_factor_[2];
    }
    ++constraint_index;
  }
  // std::cout << "constraint_index   " << constraint_index << "     line  " << __LINE__ << std::endl;

  // 长度大小等于 3*num_of_knots_
  if (constraint_index != num_of_variables)
  {
    std::cout << "Error in Calculate Affine Constraint 1" << std::endl;
  }

  //  x(i->i+1)''' = (x(i+1)'' - x(i)'') / delta_s
  // 加加速度
  for (int i = 0; i + 1 < n; ++i)
  {
    variables[2 * n + i].emplace_back(constraint_index, -1.0);
    variables[2 * n + i + 1].emplace_back(constraint_index, 1.0);
    lower_bounds->at(constraint_index) =
        dddx_bound_.first * delta_s_ * scale_factor_[2];
    upper_bounds->at(constraint_index) =
        dddx_bound_.second * delta_s_ * scale_factor_[2];
    ++constraint_index;
    if (lower_bounds->at(constraint_index) > 0)
    {
      std::cout << "error" << std::endl;
    }
  }
  // std::cout << "constraint_index   " << constraint_index << "     line  " << __LINE__ << std::endl;

  // x(i+1)' - x(i)' - 0.5 * delta_s * x(i)'' - 0.5 * delta_s * x(i+1)'' = 0
  // 速度相等
  for (int i = 0; i + 1 < n; ++i)
  {
    variables[n + i].emplace_back(constraint_index, -1.0 * scale_factor_[2]);
    variables[n + i + 1].emplace_back(constraint_index, 1.0 * scale_factor_[2]);
    variables[2 * n + i].emplace_back(constraint_index,
                                      -0.5 * delta_s_ * scale_factor_[1]);
    variables[2 * n + i + 1].emplace_back(constraint_index,
                                          -0.5 * delta_s_ * scale_factor_[1]);
    lower_bounds->at(constraint_index) = 0.0; // 等式约束
    upper_bounds->at(constraint_index) = 0.0; // 等式约束
    ++constraint_index;
  }
  // std::cout << "constraint_index   " << constraint_index << "     line  " << __LINE__ << std::endl;

  // x(i+1) - x(i) - delta_s * x(i)' - 1/3 * delta_s^2 * x(i)'' - 1/6 * delta_s^2 * x(i+1)''
  // 位置相等
  auto delta_s_sq_ = delta_s_ * delta_s_;
  for (int i = 0; i + 1 < n; ++i)
  {
    variables[i].emplace_back(constraint_index,
                              -1.0 * scale_factor_[1] * scale_factor_[2]);
    variables[i + 1].emplace_back(constraint_index,
                                  1.0 * scale_factor_[1] * scale_factor_[2]);
    variables[n + i].emplace_back(
        constraint_index, -delta_s_ * scale_factor_[0] * scale_factor_[2]);
    variables[2 * n + i].emplace_back(
        constraint_index,
        -delta_s_sq_ / 3.0 * scale_factor_[0] * scale_factor_[1]);
    variables[2 * n + i + 1].emplace_back(
        constraint_index,
        -delta_s_sq_ / 6.0 * scale_factor_[0] * scale_factor_[1]);

    lower_bounds->at(constraint_index) = 0.0; // 等式约束
    upper_bounds->at(constraint_index) = 0.0; // 等式约束
    ++constraint_index;
  }
  // std::cout << "constraint_index   " << constraint_index << "     line  " << __LINE__ << std::endl;

  // constrain on x_init  // 长度大小等于3
  // 最后是初始状态约束，即最终轨迹的初始状态要与当前车辆状态保持一致
  variables[0].emplace_back(constraint_index, 1.0);
  lower_bounds->at(constraint_index) = x_init_[0] * scale_factor_[0];
  upper_bounds->at(constraint_index) = x_init_[0] * scale_factor_[0];
  ++constraint_index;

  variables[n].emplace_back(constraint_index, 1.0);
  lower_bounds->at(constraint_index) = x_init_[1] * scale_factor_[1];
  upper_bounds->at(constraint_index) = x_init_[1] * scale_factor_[1];
  ++constraint_index;

  variables[2 * n].emplace_back(constraint_index, 1.0);
  lower_bounds->at(constraint_index) = x_init_[2] * scale_factor_[2];
  upper_bounds->at(constraint_index) = x_init_[2] * scale_factor_[2];
  ++constraint_index;

  // std::cout << "constraint_index   " << constraint_index << "     line  " << __LINE__ << std::endl;

  if (constraint_index != num_of_constraints)
  {
    std::cout << "Error in Calculate Affine Constraint 2" << std::endl;
  }

  // 组成csc_matrix的格式
  int ind_p = 0;
  for (int i = 0; i < num_of_variables; ++i)
  {
    // 每列不为0的元素的数目
    A_indptr->push_back(ind_p);
    for (const auto &variable_nz : variables[i])
    {
      // 每列不为0的元素的数值
      A_data->push_back(variable_nz.second);
      // 每列不为0的元素的索引
      A_indices->push_back(variable_nz.first);
      ++ind_p;
    }
  }
  A_indptr->push_back(ind_p);
}

//  osqp内部的核函数矩阵,计算q
// 最后，我们将进行offset 补偿，这里主要指的是 最后的参考线要考虑referline这一因素，即初始解。
// 保证尽可能不要有太大偏差，这样有可能给车辆带来不稳定因素，这里主要是给目标函数进行补偿，目标函数的 ref一项。
// 其实目标函数在横向位移上有两项： l^2+(l-ref)^2,因此可以看到为什么在目标函数里，l^2的系数乘以2，在这里将第二项进行了拆解，
//于是有了offset。 即 -2ref*i，这个就对应了。各位细品。至于为什么不考虑ref^2，因为它是个非负实数，并不包含任何变量，因此不影响梯度下降，
// 从而不影响整个函数的求解。因此在此处省略
void OSQPProblem::CalculateOffset(std::vector<c_float> *q)
{
  if (q == nullptr)
  {
    std::cout << "q should not be nullptr!!" << std::endl;
    return;
  }
  const int n = static_cast<int>(num_of_knots_);
  const int kNumParam = 3 * n;
  q->resize(kNumParam, 0.0);

  if (has_x_ref_)
  {
    for (int i = 0; i < n; ++i)
    {
      q->at(i) += -2.0 * weight_x_ref_ * x_ref_[i] / scale_factor_[0];
    }
  }

  if (has_end_state_ref_)
  {
    q->at(n - 1) +=
        -2.0 * weight_end_state_[0] * end_state_ref_[0] / scale_factor_[0];
    q->at(2 * n - 1) +=
        -2.0 * weight_end_state_[1] * end_state_ref_[1] / scale_factor_[1];
    q->at(3 * n - 1) +=
        -2.0 * weight_end_state_[2] * end_state_ref_[2] / scale_factor_[2];
  }
}

// //该函数是重点，主要包含了目标函数与响应约束的建立，以及目标函数的offset补偿
OSQPData *OSQPProblem::FormulateProblem()
{
  size_t kernel_dim = 3 * num_of_knots_;
  OSQPData *data = reinterpret_cast<OSQPData *>(c_malloc(sizeof(OSQPData)));
  // 计算 P
  std::vector<c_float> P_data;  // 每列不为0的元素的数值
  std::vector<c_int> P_indices; // 每列不为0的元素的索引
  std::vector<c_int> P_indptr;  // 每列不为0的元素的数目
  CalculateKernel(&P_data, &P_indices, &P_indptr);
  // osqp内部的核函数矩阵形式是csc格式
  data->P = csc_matrix(kernel_dim, kernel_dim, P_data.size(),
                       CopyData(P_data), CopyData(P_indices), CopyData(P_indptr));

  // calculate affine constraints  // 计算A和上下边界
  std::vector<c_float> A_data;  // 每列不为0的元素的数值
  std::vector<c_int> A_indices; // 每列不为0的元素的索引
  std::vector<c_int> A_indptr;  // 每列不为0的元素的数目
  std::vector<c_float> lower_bounds;
  std::vector<c_float> upper_bounds;
  CalculateAffineConstraint(&A_data, &A_indices, &A_indptr, &lower_bounds,
                            &upper_bounds);

  // { // debug only
  //   std::cout << "P_data " << std::endl;
  //   for (int i = 0; i < P_data.size(); i++)
  //   {
  //     std::cout << "   " << P_data[i] << " ";
  //   }
  //   std::cout << " " << std::endl;

  //   std::cout << "P_indices " << std::endl;
  //   for (int i = 0; i < P_indices.size(); i++)
  //   {
  //     std::cout << "   " << P_indices[i] << " ";
  //   }
  //   std::cout << " " << std::endl;

  //   std::cout << "P_indptr " << std::endl;
  //   for (int i = 0; i < P_indptr.size(); i++)
  //   {
  //     std::cout << "   " << P_indptr[i] << " ";
  //   }
  //   std::cout << " " << std::endl;

  //   std::cout << "  Start of P" << std::endl;
  //   int tmp_1 = 0;
  //   for (int i = 0; i < data->P->m; i++)
  //   {
  //     for (int j = 0; j < data->P->n; j++)
  //     {
  //       tmp_1 = i * 9 + j;
  //       std::cout << " " << *(data->P->x + tmp_1) << " ";
  //     }
  //     std::cout << "" << std::endl;
  //   }
  //   std::cout << "  End of P" << std::endl;

  //   std::cout << "num_of_knots_   " << num_of_knots_ << std::endl;

  //   std::cout << "A_indptr " << std::endl;
  //   for (int i = 0; i < A_indptr.size(); i++)
  //   {
  //     std::cout << "   " << A_indptr[i] << " ";
  //   }
  //   std::cout << " " << std::endl;

  //   std::cout << "A_indices " << std::endl;
  //   for (int i = 0; i < A_indices.size(); i++)
  //   {
  //     std::cout << "   " << A_indices[i] << " ";
  //   }
  //   std::cout << " " << std::endl;

  //   std::cout << "A_data " << std::endl;
  //   for (int i = 0; i < A_data.size(); i++)
  //   {
  //     std::cout << "   " << A_data[i] << " ";
  //   }
  //   std::cout << " " << std::endl;
  // }

  // calculate offset  //计算 q
  std::vector<c_float> q;
  CalculateOffset(&q);

  if (lower_bounds.size() != upper_bounds.size())
  {
    std::cout << "Formulate data failed!" << std::endl;
  }

  size_t num_affine_constraint = lower_bounds.size();
  data->n = kernel_dim;
  data->m = num_affine_constraint;
  data->q = CopyData(q);

  data->A =
      csc_matrix(num_affine_constraint, kernel_dim, A_data.size(),
                 CopyData(A_data), CopyData(A_indices), CopyData(A_indptr));

  // { //debug only

  // std::cout << "q " << std::endl;
  // for (int i = 0; i < q.size(); i++)
  // {
  //   std::cout << "   " << q[i] << " ";
  // }
  // std::cout << " " << std::endl;

  //   std::cout << "A number of rows   " << data->A->m << "  colums  " << data->A->n << std::endl;
  //   std::cout << "  Start of A" << std::endl;
  //   std::cout << "A  " << *(data->A->x + 0) << std::endl;
  //   int tmp = 0;
  //   for (int i = 0; i < data->A->m; i++)
  //   {
  //     for (int j = 0; j < data->A->n; j++)
  //     {
  //       tmp = i * 9 + j;
  //       std::cout << " " << *(data->A->x + tmp) << " ";
  //     }
  //     std::cout << "" << std::endl;
  //   }

  //   std::cout << "  End of A" << std::endl;

  //   std::cout << "lower_bounds.size()   " << lower_bounds.size() << std::endl;
  //   for (int i = 0; i < lower_bounds.size(); i++)
  //   {
  //     std::cout << lower_bounds[i] << "  ";
  //   }
  //   std::cout << "" << std::endl;
  //   for (int i = 0; i < upper_bounds.size(); i++)
  //   {
  //     std::cout << upper_bounds[i] << "  ";
  //   }
  //   std::cout << "" << std::endl;
  // }

  data->l = CopyData(lower_bounds);
  data->u = CopyData(upper_bounds);
  return data;
}

OSQPSettings *OSQPProblem::SolverDefaultSettings()
{
  // Define Solver default settings
  OSQPSettings *settings =
      reinterpret_cast<OSQPSettings *>(c_malloc(sizeof(OSQPSettings)));
  osqp_set_default_settings(settings);
  settings->eps_abs = 5e-3;
  settings->eps_rel = 5e-3;
  settings->eps_prim_inf = 5e-4;
  settings->eps_dual_inf = 5e-4;
  settings->polish = true;
  settings->verbose = false;
  settings->scaled_termination = true;
  return settings;
}

bool OSQPProblem::Optimize(const int max_iter)
{
  OSQPData *data = FormulateProblem();

  OSQPSettings *settings = SolverDefaultSettings();
  settings->max_iter = max_iter;

  OSQPWorkspace *osqp_work;

  c_int status = 0;

  status = osqp_setup(&osqp_work, data, settings);

  osqp_solve(osqp_work);

  if (status != 0)
  {
    std::cout << "failed optimization status:\t" << osqp_work->info->status
              << std::endl;
    osqp_cleanup(osqp_work);
    FreeData(data);
    c_free(settings);
    return false;
  }
  else if (osqp_work->solution == nullptr)
  {
    std::cout << "The solution from OSQP is nullptr" << std::endl;
    osqp_cleanup(osqp_work);
    FreeData(data);
    c_free(settings);
    return false;
  }

  // extract primal results
  x_.resize(num_of_knots_);
  dx_.resize(num_of_knots_);
  ddx_.resize(num_of_knots_);
  for (size_t i = 0; i < num_of_knots_; ++i)
  {
    x_.at(i) = osqp_work->solution->x[i] / scale_factor_[0];
    dx_.at(i) = osqp_work->solution->x[i + num_of_knots_] / scale_factor_[1];
    ddx_.at(i) = osqp_work->solution->x[i + 2 * num_of_knots_] / scale_factor_[2];
  }

  // Cleanup
  osqp_cleanup(osqp_work);
  FreeData(data);
  c_free(settings);
  return true;
}

void OSQPProblem::FreeData(OSQPData *data)
{
  delete[] data->q;
  delete[] data->l;
  delete[] data->u;

  delete[] data->P->i;
  delete[] data->P->p;
  delete[] data->P->x;

  delete[] data->A->i;
  delete[] data->A->p;
  delete[] data->A->x;
}

void OSQPProblem::set_end_state_ref(
    const std::array<double, 3> &weight_end_state,
    const std::array<double, 3> &end_state_ref)
{
  weight_end_state_ = weight_end_state;
  end_state_ref_ = end_state_ref;
  has_end_state_ref_ = true;
}

void OSQPProblem::set_x_ref(const double weight_x_ref,
                            std::vector<double> x_ref)
{
  if (x_ref.size() != num_of_knots_)
  {
    std::cout << "x_ref size is wrong!" << std::endl;
    return;
  }
  weight_x_ref_ = weight_x_ref;
  x_ref_ = x_ref;
  has_x_ref_ = true;
}

void OSQPProblem::set_dx_bounds(double low_bound, double up_bound)
{
  for (auto &x : dx_bounds_)
  {
    x.first = low_bound;
    x.second = up_bound;
  }
}

void OSQPProblem::set_ddx_bounds(double low_bound, double up_bound)
{
  for (auto &x : ddx_bounds_)
  {
    x.first = low_bound;
    x.second = up_bound;
  }
}

void OSQPProblem::set_dddx_bounds(double low, double up)
{
  dddx_bound_.first = low;
  dddx_bound_.second = up;
}
