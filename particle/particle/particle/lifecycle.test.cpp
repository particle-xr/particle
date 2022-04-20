#include "particle/lifecycle.hpp"

#include <cstdlib>

using namespace particle;

constexpr int YEAR_IN_DAYS = 365;
constexpr int END_OF_WINTER = 90;
constexpr int END_OF_SPRING = 185;
constexpr int END_OF_SUMMER = 280;

// TODO: Create a test harness for some Lifecycle<Organism>

int
main(int argc, char* argv[])
{
  Lifecycle<int> lifecycle;

  for (auto i = 0; i <= YEAR_IN_DAYS; i++) {
    if (i < END_OF_WINTER) {
      if (i % 4 == 0) {
        // It snows.
      } else {
        // It's sunny, but cold.
      }
    } else if (i >= END_OF_WINTER && i < END_OF_SPRING) {
      if (i % 4 == 0) {
        // It rains.
      } else {
        // It's sunny and warm.
      }
    } else if (i >= END_OF_SPRING && i < END_OF_SUMMER) {
      if (i % 7 == 0) {
        // It rains.
      } else {
        // It's sunny and hot.
      }
    } else {
      if (i % 6 == 0) {
        // It rains.
      } else {
        // It's sunny and cool.
      }
    }
  }

  return EXIT_SUCCESS;
}
