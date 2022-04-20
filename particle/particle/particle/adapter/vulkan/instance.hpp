#pragma once

#include "particle/adapter/vulkan.hpp"
#include "particle/adapter/vulkan/debugger.hpp"

#include <memory>
#include <string>
#include <vector>

namespace particle::vulkan {

class Debugger;
class Device;
class SwapChain;

class Instance
{
public:
  using type = Instance;

  Instance(std::string name, bool enable_validation);
  ~Instance();

  bool validation_enabled() const;

private:
  vk::Instance instance();
  vk::Device device();

private:
  std::string name_;
  bool validation_enabled_ = false;
  std::vector<const char*> supported_extensions_;
  std::vector<const char*> requested_extensions_;
  vk::UniqueInstance instance_;

private:
  std::unique_ptr<Debugger> debugger_;

private:
  vk::PhysicalDevice physical_device_;
  vk::PhysicalDeviceProperties physical_device_properties_;
  vk::PhysicalDeviceFeatures physical_device_features_;
  vk::PhysicalDeviceMemoryProperties physical_device_memory_properties_;

private:
  vk::UniqueDevice logical_device_;

private:
  vk::UniqueCommandPool command_pool_;
  vk::UniqueCommandBuffer command_buffer_;
};

}
