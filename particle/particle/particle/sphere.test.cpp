#include "particle/sphere.hpp"

#include "particle/forces.hpp"
#include "particle/forces/displacement.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <iostream>

using namespace particle;

TEST_CASE("apply single force")
{
  Sphere s{ { 0, 0, 0 }, 100 };
  Force<Displacement<X>> f{ 10 };

  f(s);

  CHECK(s.origin() == Dimensional<3>{ 10, 0, 0 });
}

TEST_CASE("apply multiple forces")
{
  Sphere s{ { 0, 0, 0 }, 100 };
  Forces<Displacement<X>, Displacement<Y>, Displacement<Z>> f{ 10, 5, -1 };

  f(s);

  CHECK(s.origin() == Dimensional<3>{ 10, 5, -1 });
}
