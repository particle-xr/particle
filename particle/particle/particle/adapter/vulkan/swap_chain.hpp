#pragma once

#include "particle/adapter/vulkan.hpp"

namespace particle::vulkan {

class SwapChain
{
public:
  using type = SwapChain;

  void connect(VkInstance, VkPhysicalDevice, VkDevice);
};

}
