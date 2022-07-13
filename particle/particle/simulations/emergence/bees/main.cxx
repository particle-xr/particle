#include "particle/macros.hxx"
#include "particle/point.hxx"
#include "particle/version.hxx"
#include "particle/world.hxx"

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

/*
 * This simulation will focus on the behavior of a beehive.
 * For the purposes of simplicity, the sole purpose of the beehive will be to
 * seek out flowerbeds which can be pollinated.
 *
 * Initially, the bees will each go off in random directions in search of
 * flowerbeds. When they find one, they will begin to pollinate it by moving
 * from flower to flower (thus pollenating) until the flower is either "fully
 * pollenated" or "has no more pollen to give". Bees will periodically return to
 * the hive, if only for the sake of the simulation, to encourage
 * "communication" of pollination progress and the discovery of new flowerbeds.
 *
 * Flowers will be color coded, such that cross-pollination can be identified
 * visually as various flowers will change color when cross-pollinated with a
 * flower of a different color.
 *
 * The bees will have a very short memory, so they will frequently revisit
 * flowerbeds and flowers which they themselves have fully pollinated. The bees
 * "memory" should be an input which can be changed dynamically, such as to
 * reduce the likelihood that a bee will revisit a flower(bed) that it has
 * knowing fully pollinated.
 *
 * Additionally, we want the bees to "communicate" their progress with other
 * bees, such that fully pollinated flowerbeds will eventually be excluded from
 * pollination routes, and also new flowerbeds will draw more bees as the
 * discovery is "communicated" throughout the hive.
 */

using namespace particle;

class Beehive;
class Bee;

class Beehive
{
public:
  using type = Beehive;

  Beehive() = default;
};

template<typename>
class Behavior;

template<typename>
class Lifecycle;

template<>
class Lifecycle<Bee>
{
public:
  using type = Lifecycle;

  Lifecycle(Bee& bee)
  {
    thread_ = std::make_unique<std::jthread>([&bee]() {
      // TODO: The lifecycle of bee would obviously start with its creation...
      // thus it doesn't seem right to have the Bee own the Lifecycle?
      // In any case... a new bee has been born! Now what?
      // Start looking for flowers! Or start building a beehive?
    });
  }

private:
  std::unique_ptr<std::jthread> thread_;
};

template<>
class Behavior<Bee>
{
public:
  using type = Behavior;

  void operator()()
  {
    //
  }
};

class Bee
{
public:
  using type = Bee;

  Bee()
  {
    // N.B. jthread?
    lifecycle_ = std::make_unique<Lifecycle<Bee>>(*this);
  }

private:
  std::unique_ptr<Lifecycle<type>> lifecycle_;
};

std::atomic_bool should_exit = false;

void
signal_handler(int)
{
  should_exit = true;
}

int
main(int argc, char* argv[])
{
  assert(should_exit.is_lock_free());
  std::signal(SIGINT, signal_handler);

  std::cout << "Hello, world" << std::endl;
  std::cout << "Using particle v" << particle::version() << std::endl;

  // TODO: Make these inputs
  const int height = 100;
  const int width = 100;
  const int n = 100;

  // A 100x100 2d world
  World<2> world{ height, width };
  std::cout << PARTICLE_SHOW(world.center()) << std::endl;

  std::vector<std::unique_ptr<Bee>> bees;
  for (auto i = 0; i < n; ++i) {
    bees.emplace_back(std::make_unique<Bee>());
  }

  std::thread t([]() {
    while (!should_exit)
      ;
  });
  t.join();

  std::cout << std::endl << "Goodbye, world" << std::endl;

  return EXIT_SUCCESS;
}
