#pragma once

#include "particle/layer.hpp"

namespace particle {

struct Simulation;

template<>
class Layer<Simulation>
{
public:
  using type = Layer;

  Layer();
  ~Layer();
};

}
