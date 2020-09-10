//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_SPEEDDATA_HPP_
#define APOLLO_SPEED_INCLUDE_SPEEDDATA_HPP_
#include <vector>
#include "SpeedPoint.hpp"
class SpeedData : public std::vector<SpeedPoint> {
 public:
    SpeedData() = default;
    virtual ~SpeedData() = default;
    explicit SpeedData(std::vector<SpeedPoint> speed_points);
    void AppendSpeedPoint(const double s, const double time, const double v,
                          const double a, const double da);
    bool EvaluateByTime(const double time,
                        SpeedPoint* const speed_point) const;
    // Assuming spatial traversed distance is monotonous, which is the case for
    // current usage on city driving scenario
    bool EvaluateByS(const double s, SpeedPoint* const speed_point) const;
    double TotalTime() const;
    // Assuming spatial traversed distance is monotonous
    double TotalLength() const;
};

#endif //APOLLO_SPEED_INCLUDE_SPEEDDATA_HPP_
