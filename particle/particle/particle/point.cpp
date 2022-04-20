#include "particle/point.hpp"

#include <iostream>

using namespace particle;

Point::Point(double x, double y)
  : x_(x)
  , y_(y)
{}

auto
Point::operator+=(const X& x) -> type&
{
  return (x_ += x, *this);
}

auto
Point::operator+=(const Y& y) -> type&
{
  return (y_ += y, *this);
}

namespace particle {

std::ostream&
operator<<(std::ostream& os, const Point& p)
{
  return os << "{" << p.x_ << "," << p.y_ << "}";
}

bool
operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}

bool
operator!=(const Point& lhs, const Point& rhs)
{
  return !(lhs == rhs);
}

}
