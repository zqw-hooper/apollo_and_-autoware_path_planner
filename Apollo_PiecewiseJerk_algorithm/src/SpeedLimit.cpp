//
// Created by ljn on 20-5-25.
//
#include <algorithm>
#include "SpeedLimit.hpp"
#include "glog/logging.h"
void SpeedLimit::AppendSpeedLimit(const double s, const double v) {
    if (!speed_limit_points_.empty()) {
        DCHECK_GE(s, speed_limit_points_.back().first);
    }
    speed_limit_points_.emplace_back(s, v);
}

const std::vector<std::pair<double, double>>& SpeedLimit::speed_limit_points()
const {
    return speed_limit_points_;
}

double SpeedLimit::GetSpeedLimitByS(const double s) const {
    CHECK_GE(speed_limit_points_.size(), 2);
    DCHECK_GE(s, speed_limit_points_.front().first);

    auto compare_s = [](const std::pair<double, double>& point, const double s) {
      return point.first < s;
    };

    auto it_lower = std::lower_bound(speed_limit_points_.begin(),
                                     speed_limit_points_.end(), s, compare_s);

    if (it_lower == speed_limit_points_.end()) {
        return (it_lower - 1)->second;
    }
    return it_lower->second;
}

void SpeedLimit::Clear() { speed_limit_points_.clear(); }