#pragma once

namespace particle {

class MilesPerHour
{
public:
  using type = MilesPerHour;

  template<typename I>
  MilesPerHour(I i)
    : value_(i)
  {}

private:
  double value_;
};

MilesPerHour operator""_mph(long double i);

constexpr double
Velocity(double v0, double a, double t)
{
  return v0 + a * t;
}

}
