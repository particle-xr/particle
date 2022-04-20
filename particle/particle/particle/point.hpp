#pragma once

#include "particle/dimensional.hpp"

#include <iostream>

namespace particle {

class Point
{
public:
  using type = Point;

  Point(double x, double y);

  // TODO: Do we want this to satisfy displaceable?
  // I think we do.
  type& operator+=(const X& x);

  type& operator+=(const Y& y);

  friend bool operator==(const type& lhs, const type& rhs);

  friend bool operator!=(const type& lhs, const type& rhs);

  friend std::ostream& operator<<(std::ostream&, const type&);

private:
  X x_;
  Y y_;
};

}
