#include "particle/adapter/vulkan/application.hpp"
#include "particle/adapter/vulkan/debugger.hpp"
#include "particle/adapter/vulkan/instance.hpp"

#include <vulkan/vulkan.h>

#include <cassert>

using namespace particle;
using namespace particle::vulkan;

Application::Application(std::string name, int argc, char* argv[])
{
  bool enable_validation = true;
  // TODO: Commandline parsing
  instance_ = std::make_unique<Instance>(name, enable_validation);

  if (instance().validation_enabled()) {
    VkDebugReportFlagsEXT debug_report_flags =
      VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    debugger_ = std::make_unique<Debugger>(debug_report_flags, VK_NULL_HANDLE);
    (*instance_)(*debugger_);
  }
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
{
  // TODO: I wonder if it would be better to create the Instance here?
}
