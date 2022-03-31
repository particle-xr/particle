#pragma once

namespace particle {

class World
{
public:
  using type = World;

  World(double gravity)
    : gravity_(gravity)
  {}

private:
  const double gravity_;
};

}
