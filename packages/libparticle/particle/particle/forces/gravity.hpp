#pragma once

#include "particle/forces.hpp"

namespace particle {

static constexpr float G = 6.67e-11;

struct Gravity;

template<>
class Force<Gravity>
{
public:
  using type = Force;
  using force_type = Gravity;

  Force(double gravity)
    : gravity_(gravity)
  {}

  template<typename T>
  void operator()(T& t)
  {
    // Apply forces.
  }

private:
  const double gravity_;
};

constexpr float
GravitationalForce(double m1, double m2, double r)
{
  return G * (m1 * m2) / (r * r);
}

}
