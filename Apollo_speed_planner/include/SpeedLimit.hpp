//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_SPEEDLIMIT_HPP_
#define APOLLO_SPEED_INCLUDE_SPEEDLIMIT_HPP_
#include <utility>
#include <vector>

class SpeedLimit {
 public:
    SpeedLimit() = default;

    void AppendSpeedLimit(const double s, const double v);

    const std::vector<std::pair<double, double>>& speed_limit_points() const;

    double GetSpeedLimitByS(const double s) const;

    void Clear();

 private:
    // use a vector to represent speed limit
    // the first number is s, the second number is v
    // It means at distance s from the start point, the speed limit is v.
    std::vector<std::pair<double, double>> speed_limit_points_;
};

#endif //APOLLO_SPEED_INCLUDE_SPEEDLIMIT_HPP_
