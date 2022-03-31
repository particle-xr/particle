#include "particle/kinematics.hpp"

namespace particle {

MilesPerHour operator""_mph(long double i)
{
  return MilesPerHour{ i };
}

}
