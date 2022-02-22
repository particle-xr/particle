#include "particle/adapter/vulkan/utils.hpp"

using namespace particle::vulkan::utils;

vk::UniqueDevice
createDeviceUnique(const vk::PhysicalDevice& physical_device,
                   uint32_t queue_family_index,
                   const std::vector<std::string>& extensions,
                   const vk::PhysicalDeviceFeatures* physical_device_features,
                   const void* p_next)
{
  std::vector<const char*> enabled_extensions;
  enabled_extensions.reserve(extensions.size());
  for (const auto& extension : extensions) {
    enabled_extensions.push_back(extension.data());
  }

  float queue_priority = 0.0f;
  // clang-format off
  vk::DeviceQueueCreateInfo device_queue_create_info{ .queueFamilyIndex = queue_family_index,
                                                      .queueCount = 1,
                                                      .pQueuePriorities = &queue_priority };
  // clang-format on
  vk::DeviceCreateInfo device_create_info{
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &device_queue_create_info,
    .enabledExtensionCount = static_cast<uint32_t>(enabled_extensions.size()),
    .ppEnabledExtensionNames = enabled_extensions.data(),
    .pEnabledFeatures = physical_device_features
  };
  device_create_info.pNext = p_next;

  return physical_device.createDeviceUnique(device_create_info);
}
