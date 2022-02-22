#pragma once

#include "particle/adapter/vulkan.hpp"

#include <string>
#include <vector>

namespace particle::vulkan {

class SwapChain;

struct QueueFamilyIndices
{
  std::uint32_t graphics;
  std::uint32_t compute;
  std::uint32_t transfer;
};

class Device
{
public:
  using type = Device;

  Device(vk::PhysicalDevice, vk::PhysicalDeviceFeatures, std::vector<const char*>, void*, bool, vk::QueueFlags, bool);
  ~Device();

  vk::Queue get_device_queue() const;
  vk::Format get_depth_format() const;

  void connect_swap_chain(SwapChain&, VkInstance);
  vk::Semaphore create_semaphore(vk::SemaphoreCreateInfo&);

private:
  std::uint32_t get_queue_family_index(vk::QueueFlags) const;

private:
  vk::PhysicalDevice physical_device_;
  vk::Device logical_device_;
  vk::PhysicalDeviceProperties properties_;
  vk::PhysicalDeviceFeatures features_;
  vk::PhysicalDeviceFeatures enabled_features_;
  vk::PhysicalDeviceMemoryProperties memory_properties_;
  std::vector<vk::QueueFamilyProperties> queue_family_properties_;
  QueueFamilyIndices queue_family_indices_;
  std::vector<std::string> supported_extensions_;
  vk::CommandPool command_pool_;
  bool debug_markers_enabled_ = false;
};

}
