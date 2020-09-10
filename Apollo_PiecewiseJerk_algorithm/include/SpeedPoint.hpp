//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_SPEEDPOINT_HPP_
#define APOLLO_SPEED_INCLUDE_SPEEDPOINT_HPP_

class SpeedPoint {
 public:
    SpeedPoint() = default;
    SpeedPoint(double s, double t, double v, double a, double da)
        : s_(s), t_(t), v_(v), a_(a), da_(da) {}
    double s_ = 0, t_ = 0, v_ = 0, a_ = 0, da_ = 0;
};

#endif //APOLLO_SPEED_INCLUDE_SPEEDPOINT_HPP_
