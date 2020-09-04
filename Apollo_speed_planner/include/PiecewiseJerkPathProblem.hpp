//
// Created by ljn on 20-5-26.
//

#ifndef APOLLO_SPEED_INCLUDE_PIECEWISEJERKPATHPROBLEM_HPP_
#define APOLLO_SPEED_INCLUDE_PIECEWISEJERKPATHPROBLEM_HPP_
#include <utility>
#include <vector>
#include "PiecewiseJerkProblem.hpp"

class PiecewiseJerkPathProblem : public PiecewiseJerkProblem{
 public:
    PiecewiseJerkPathProblem(const size_t num_of_knots, const double delta_s,
                             const std::array<double, 3>& x_init);

    ~PiecewiseJerkPathProblem() override = default;

 protected:
    void CalculateKernel(std::vector<c_float>* P_data,
                         std::vector<c_int>* P_indices,
                         std::vector<c_int>* P_indptr) override;

    void CalculateOffset(std::vector<c_float>* q) override;
};

#endif //APOLLO_SPEED_INCLUDE_PIECEWISEJERKPATHPROBLEM_HPP_
