//
// Created by ljn on 20-5-26.
//

#ifndef APOLLO_SPEED_INCLUDE_PIECEWISEJERKTRAJECTORY1D_HPP_
#define APOLLO_SPEED_INCLUDE_PIECEWISEJERKTRAJECTORY1D_HPP_
#include <string>
#include <vector>
#include "Curve1d.hpp"
#include "ConstantJerkTrajectory1d.hpp"

class PiecewiseJerkTrajectory1d : public Curve1d {
 public:
    PiecewiseJerkTrajectory1d(const double p, const double v, const double a);

    virtual ~PiecewiseJerkTrajectory1d() = default;

    double Evaluate(const std::uint32_t order, const double param) const;

    double ParamLength() const;

    std::string ToString() const;

    void AppendSegment(const double jerk, const double param);

 private:
    std::vector<ConstantJerkTrajectory1d> segments_;

    double last_p_;

    double last_v_;

    double last_a_;

    std::vector<double> param_;
};

#endif //APOLLO_SPEED_INCLUDE_PIECEWISEJERKTRAJECTORY1D_HPP_
