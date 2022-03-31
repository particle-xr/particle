#pragma once

#include "particle/dimensional.hpp"
#include "particle/forces/displacement.hpp"

#include <vector>

namespace particle {

class Sphere
{
public:
  using type = Sphere;

  // TODO: Interesting question here:
  // Should the Sphere know where it is in the world?
  // Or should the world know where the sphere is?
  Sphere(Dimensional<3> origin, double radius);

  const Dimensional<3>& origin();

  template<typename D>
  void displace(const auto& f)
  {
    origin_.displace<D>(f);
  }

private:
  Dimensional<3> origin_;
  std::vector<float> vertices_;
};

}
