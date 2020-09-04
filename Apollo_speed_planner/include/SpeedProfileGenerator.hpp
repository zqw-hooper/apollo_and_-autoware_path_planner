//
// Created by ljn on 20-5-27.
//

#ifndef APOLLO_SPEED_INCLUDE_SPEEDPROFILEGENERATOR_HPP_
#define APOLLO_SPEED_INCLUDE_SPEEDPROFILEGENERATOR_HPP_
#include <vector>
#include "SpeedData.hpp"
class SpeedProfileGenerator {
 public:
    SpeedProfileGenerator() = delete;

//    static SpeedData GenerateFallbackSpeed(const double stop_distance = 0.0);

    static void FillEnoughSpeedPoints(SpeedData* const speed_data);

//    static SpeedData GenerateFixedDistanceCreepProfile(const double distance,
//                                                       const double max_speed);

 private:
//    static SpeedData GenerateStopProfile(const double init_speed,
//                                         const double init_acc);
};

#endif //APOLLO_SPEED_INCLUDE_SPEEDPROFILEGENERATOR_HPP_
