//
// Created by ljn on 20-5-25.
//
#include <algorithm>
#include <utility>
#include "glog/logging.h"
#include "SpeedData.hpp"
#include "math.hpp"

SpeedData::SpeedData(std::vector<SpeedPoint> speed_points)
    : std::vector<SpeedPoint>(std::move(speed_points)) {
    std::sort(begin(), end(), [](const SpeedPoint& p1, const SpeedPoint& p2) {
      return p1.t_ < p2.t_;
    });
}

void SpeedData::AppendSpeedPoint(const double s, const double time,
                                 const double v, const double a,
                                 const double da) {
    if (!empty()) {
        CHECK(back().t_ < time);
    }
    emplace_back(s, time, v, a, da);
}

bool SpeedData::EvaluateByTime(const double t,
                               SpeedPoint* const speed_point) const {
    if (size() < 2) {
        return false;
    }
    if (!(front().t_ < t + 1.0e-6 && t - 1.0e-6 < back().t_)) {
        return false;
    }

    auto comp = [](const SpeedPoint& sp, const double t) {
      return sp.t_ < t;
    };

    auto it_lower = std::lower_bound(begin(), end(), t, comp);
    if (it_lower == end()) {
        *speed_point = back();
    } else if (it_lower == begin()) {
        *speed_point = front();
    } else {
        const auto& p0 = *(it_lower - 1);
        const auto& p1 = *it_lower;
        double t0 = p0.t_;
        double t1 = p1.t_;

        speed_point->s_ = lerp(p0.s_, t0, p1.s_, t1, t);
        speed_point->t_ = t;
        speed_point->v_ = lerp(p0.v_, t0, p1.v_, t1, t);
        speed_point->a_ = lerp(p0.a_, t0, p1.a_, t1, t);
        speed_point->da_ = lerp(p0.da_, t0, p1.da_, t1, t);
    }
    return true;
}

bool SpeedData::EvaluateByS(const double s,
                            SpeedPoint* const speed_point) const {
    if (size() < 2) {
        return false;
    }
    if (!(front().s_ < s + 1.0e-6 && s - 1.0e-6 < back().s_)) {
        return false;
    }

    auto comp = [](const SpeedPoint& sp, const double s) {
      return sp.s_ < s;
    };

    auto it_lower = std::lower_bound(begin(), end(), s, comp);
    if (it_lower == end()) {
        *speed_point = back();
    } else if (it_lower == begin()) {
        *speed_point = front();
    } else {
        const auto& p0 = *(it_lower - 1);
        const auto& p1 = *it_lower;
        double s0 = p0.s_;
        double s1 = p1.s_;

        speed_point->s_ = s;
        speed_point->t_ = lerp(p0.t_, s0, p1.t_, s1, s);
        speed_point->v_ = lerp(p0.v_, s0, p1.v_, s1, s);
        speed_point->a_ = lerp(p0.a_, s0, p1.a_, s1, s);
        speed_point->da_ = lerp(p0.da_, s0, p1.da_, s1, s);
    }
    return true;
}

double SpeedData::TotalTime() const {
    if (empty()) {
        return 0.0;
    }
    return back().t_ - front().t_;
}

double SpeedData::TotalLength() const {
    if (empty()) {
        return 0.0;
    }
    return back().s_ - front().s_;
}

