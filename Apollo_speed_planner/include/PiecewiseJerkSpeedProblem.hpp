//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_PIECEWISEJERKSPEEDPROBLEM_HPP_
#define APOLLO_SPEED_INCLUDE_PIECEWISEJERKSPEEDPROBLEM_HPP_
#include "PiecewiseJerkProblem.hpp"
class PiecewiseJerkSpeedProblem : public PiecewiseJerkProblem {
 public:
    PiecewiseJerkSpeedProblem(const size_t num_of_knots, const double delta_s,
                              const std::array<double, 3>& x_init);

    virtual ~PiecewiseJerkSpeedProblem() = default;

    void set_dx_ref(const double weight_dx_ref, const double dx_ref);

    void set_penalty_dx(std::vector<double> penalty_dx);

 protected:
    // naming convention follows osqp solver.
    void CalculateKernel(std::vector<c_float>* P_data,
                         std::vector<c_int>* P_indices,
                         std::vector<c_int>* P_indptr) override;

    void CalculateOffset(std::vector<c_float>* q) override;

    OSQPSettings* SolverDefaultSettings() override;

    bool has_dx_ref_ = false;
    double weight_dx_ref_ = 0.0;
    double dx_ref_ = 0.0;

    std::vector<double> penalty_dx_;
};

#endif //APOLLO_SPEED_INCLUDE_PIECEWISEJERKSPEEDPROBLEM_HPP_
