//
// Created by ljn on 20-5-26.
//

#ifndef APOLLO_SPEED_INCLUDE_CURVE1D_HPP_
#define APOLLO_SPEED_INCLUDE_CURVE1D_HPP_
#include <string>

class Curve1d {
 public:
    Curve1d() = default;

    virtual ~Curve1d() = default;

    virtual double Evaluate(const std::uint32_t order,
                            const double param) const = 0;

    virtual double ParamLength() const = 0;

    virtual std::string ToString() const = 0;
};

#endif //APOLLO_SPEED_INCLUDE_CURVE1D_HPP_
