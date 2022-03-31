#include "particle/gravity.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <iostream>

using namespace particle;

TEST_CASE("Gravitational force is computed")
{
  CHECK(GravitationalForce(5000000, 900000, 30) == 0.3335f);
}
