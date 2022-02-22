#pragma once

#include "particle/adapter/vulkan.hpp"

namespace particle::vulkan {

class Debugger
{
public:
  using type = Debugger;

  Debugger(vk::Instance instance);
  ~Debugger();

private:
  vk::Instance instance_;
  vk::UniqueDebugUtilsMessengerEXT debug_messenger_;
};

}
