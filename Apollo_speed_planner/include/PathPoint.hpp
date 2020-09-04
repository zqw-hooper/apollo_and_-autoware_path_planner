//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_PATHPOINT_HPP_
#define APOLLO_SPEED_INCLUDE_PATHPOINT_HPP_

class PathPoint {
 public:
    double x_ = 0;
    double y_ = 0;
    double z_ = 0;
    double theta_ = 0;
    double kappa_ = 0;
    double s_ = 0;
    double dkappa_ = 0;
    double ddkappa_ = 0;
    double x_derivative_ = 0;
    double y_derivative_ = 0;

};

#endif //APOLLO_SPEED_INCLUDE_PATHPOINT_HPP_
