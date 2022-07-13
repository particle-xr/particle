#include "particle/point.hxx"

#include <iostream>

namespace particle {

Point<2>::Point(int x, int y)
  : x_(x)
  , y_(y)
{}

std::ostream&
operator<<(std::ostream& os, const Point<2>& p)
{
  return os << "{" << p.x_ << "," << p.y_ << "}";
}

bool
operator==(const Point<2>& lhs, const Point<2>& rhs)
{
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}

bool
operator!=(const Point<2>& lhs, const Point<2>& rhs)
{
  return !(lhs == rhs);
}

}
