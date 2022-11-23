#pragma once

#include "particle/dimensional.hpp"

#include <iosfwd>

namespace particle {

template<int D>
class Point;

template<>
class Point<2>
{
public:
  using type = Point;

  Point(int x, int y);

  friend bool operator==(const type&, const type&);
  friend bool operator!=(const type&, const type&);

  friend std::ostream& operator<<(std::ostream&, const type&);

private:
  int x_;
  int y_;
};

}
