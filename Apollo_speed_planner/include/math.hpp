//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_MATH_HPP_
#define APOLLO_SPEED_INCLUDE_MATH_HPP_

class PathPoint;

double NormalizeAngle(const double angle);

double slerp(const double a0, const double t0, const double a1, const double t1,
             const double t);

template <typename T>
T lerp(const T &x0, const double t0, const T &x1, const double t1,
       const double t) {
    if (std::abs(t1 - t0) <= 1.0e-6) {
        return x0;
    }
    const double r = (t - t0) / (t1 - t0);
    const T x = x0 + r * (x1 - x0);
    return x;
}

PathPoint InterpolateUsingLinearApproximation(const PathPoint &p0,
                                              const PathPoint &p1,
                                              const double s);
#endif //APOLLO_SPEED_INCLUDE_MATH_HPP_
