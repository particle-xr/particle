#pragma once

#include "particle/adapter/vulkan.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#define VK_CHECK_RESULT(f)                                                     \
  {                                                                            \
    VkResult result = (f);                                                     \
    if (result != VK_SUCCESS) {                                                \
      std::cerr << "FATAL: Expected VK_SUCCESS but got \""                     \
                << std::to_string(result) << "\" at " << __FILE__ << ":"       \
                << __LINE__ << std::endl;                                      \
      assert(result == VK_SUCCESS);                                            \
    }                                                                          \
  }

namespace particle::vulkan::utils {

vk::UniqueDevice
createDeviceUnique(const vk::PhysicalDevice&,
                   uint32_t,
                   const std::vector<std::string>& = {},
                   const vk::PhysicalDeviceFeatures* = nullptr,
                   const void* = nullptr);

}
