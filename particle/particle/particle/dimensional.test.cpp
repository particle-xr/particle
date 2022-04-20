#include "particle/dimensional.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace particle;

TEST_CASE("2d")
{
  Dimensional<2> d{ 0, 0 };
  CHECK(d.x() == 0);
  CHECK(d.y() == 0);
}

TEST_CASE("3d")
{
  Dimensional<3> d{ 0, 0, 0 };
  CHECK(d.x() == 0);
  CHECK(d.y() == 0);
  CHECK(d.z() == 0);
}
