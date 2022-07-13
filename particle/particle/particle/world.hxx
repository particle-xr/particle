#pragma once

#include "particle/point.hxx"

namespace particle {

template<int Dimensionality>
class World;

template<>
class World<2>
{
public:
  using type = World;

  World(int h, int w);

  const Point<2>& center() const;

private:
  const int height_;
  const int width_;
  const Point<2> center_;
};

}
