//
// Created by ljn on 20-5-26.
//
#include <cmath>
#include "PathPoint.hpp"
#include "math.hpp"

constexpr double kMathEpsilon = 1e-10;

double NormalizeAngle(const double angle) {
    double a = std::fmod(angle + M_PI, 2.0 * M_PI);
    if (a < 0.0) {
        a += (2.0 * M_PI);
    }
    return a - M_PI;
}

double slerp(const double a0, const double t0, const double a1, const double t1,
             const double t) {
    if (std::abs(t1 - t0) <= kMathEpsilon) {
        return NormalizeAngle(a0);
    }
    const double a0_n = NormalizeAngle(a0);
    const double a1_n = NormalizeAngle(a1);
    double d = a1_n - a0_n;
    if (d > M_PI) {
        d = d - 2 * M_PI;
    } else if (d < -M_PI) {
        d = d + 2 * M_PI;
    }

    const double r = (t - t0) / (t1 - t0);
    const double a = a0_n + d * r;
    return NormalizeAngle(a);
}

PathPoint InterpolateUsingLinearApproximation(const PathPoint &p0,
                                              const PathPoint &p1,
                                              const double s) {
    double s0 = p0.s_;
    double s1 = p1.s_;

    PathPoint path_point;
    double weight = (s - s0) / (s1 - s0);
    double x = (1 - weight) * p0.x_ + weight * p1.x_;
    double y = (1 - weight) * p0.y_ + weight * p1.y_;
    double theta = slerp(p0.theta_, p0.s_, p1.theta_, p1.s_, s);
    double kappa = (1 - weight) * p0.kappa_ + weight * p1.kappa_;
    double dkappa = (1 - weight) * p0.dkappa_ + weight * p1.dkappa_;
    double ddkappa = (1 - weight) * p0.ddkappa_ + weight * p1.ddkappa_;
    path_point.x_ = (x);
    path_point.y_ = (y);
    path_point.theta_ = (theta);
    path_point.kappa_ = (kappa);
    path_point.dkappa_ = (dkappa);
    path_point.ddkappa_ = (ddkappa);
    path_point.s_ = (s);
    return path_point;
}