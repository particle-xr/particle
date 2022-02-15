#include <particle/adapter/vulkan/application.hpp>
#include <particle/version.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>

using namespace particle;

class TriangleApplication : public vulkan::Application
{
public:
  using type = TriangleApplication;
  using parent_type = vulkan::Application;

  TriangleApplication(int argc, char* argv[])
    : parent_type("Triangle", argc, argv)
  {}
  ~TriangleApplication() override {}
};

int
main(int argc, char* argv[])
{
  std::cout << "Using libparticle version " << get_version() << std::endl;

  auto app = std::make_unique<TriangleApplication>(argc, argv);

  try {
    app->run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
