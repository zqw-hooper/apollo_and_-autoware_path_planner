//
// Created by ljn on 20-5-25.
//

#ifndef APOLLO_SPEED_INCLUDE_DISCRETIZEDPATH_HPP_
#define APOLLO_SPEED_INCLUDE_DISCRETIZEDPATH_HPP_
#include <vector>
#include "PathPoint.hpp"
 class DiscretizedPath : public std::vector<PathPoint> {
  public:
     DiscretizedPath() = default;

     explicit DiscretizedPath(std::vector<PathPoint> path_points);

     double Length() const;

     PathPoint Evaluate(const double path_s) const;

     PathPoint EvaluateReverse(const double path_s) const;

  protected:
     std::vector<PathPoint>::const_iterator QueryLowerBound(
         const double path_s) const;
     std::vector<PathPoint>::const_iterator QueryUpperBound(
         const double path_s) const;
};

#endif //APOLLO_SPEED_INCLUDE_DISCRETIZEDPATH_HPP_
