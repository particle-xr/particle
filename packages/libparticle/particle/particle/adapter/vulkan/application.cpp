#include "particle/adapter/vulkan/application.hpp"
#include "particle/adapter/vulkan/instance.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>

using namespace particle;
using namespace particle::vulkan;

Application::Application(std::string name, int argc, char* argv[])
{
  bool enable_validation = true;
  // TODO: Commandline parsing
  instance_ = std::make_unique<Instance>(name, enable_validation);
}

/* virtual */ Application::~Application() = default;

Instance&
Application::instance()
{
  assert(instance_);
  return *instance_;
}

void
Application::run()
{}
