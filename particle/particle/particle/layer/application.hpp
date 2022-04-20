#pragma once

#include "particle/layer.hpp"

namespace particle {

struct Application;

template<>
class Layer<Application>
{
public:
  using type = Layer;

  Layer();
  ~Layer();
};

}
