#include "particle/kinematics.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace particle;

TEST_CASE("Linear velocity is computed")
{
  CHECK(Velocity(10, 5, 5) == 35.0);
}
