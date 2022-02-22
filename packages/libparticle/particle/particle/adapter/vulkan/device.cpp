#include "particle/adapter/vulkan/device.hpp"
#include "particle/adapter/vulkan/swap_chain.hpp"
#include "particle/adapter/vulkan/utils.hpp"

#include <cassert>
#include <iostream>

using namespace particle::vulkan;

Device::Device(vk::PhysicalDevice physical_device,
               vk::PhysicalDeviceFeatures enabled_features,
               std::vector<const char*> enabled_extensions,
               void* next_chain,
               bool use_swap_chain,
               vk::QueueFlags requested_queue_types,
               bool use_debug_markers)
  : physical_device_(physical_device)
  , enabled_features_(enabled_features)
  , debug_markers_enabled_(use_debug_markers)
{
  properties_ = physical_device.getProperties();
  features_ = physical_device.getFeatures();
  memory_properties_ = physical_device.getMemoryProperties();

  std::uint32_t queue_family_count;
  vkGetPhysicalDeviceQueueFamilyProperties(
    physical_device_, &queue_family_count, nullptr);
  assert(queue_family_count > 0);
  queue_family_properties_.resize(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(
    physical_device_, &queue_family_count, &queue_family_properties_.front());

  std::uint32_t extension_count = 0;
  vkEnumerateDeviceExtensionProperties(
    physical_device_, nullptr, &extension_count, nullptr);
  if (extension_count > 0) {
    std::vector<VkExtensionProperties> extensions(extension_count);
    if (vkEnumerateDeviceExtensionProperties(
          physical_device_, nullptr, &extension_count, &extensions.front()) ==
        VK_SUCCESS) {
      for (auto extension : extensions) {
        supported_extensions_.push_back(extension.extensionName);
      }
    }
  }

  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  const float default_queue_priority = 0.0f;

  const bool use_graphics_queue = true;
  if (use_graphics_queue) {
    queue_family_indices_.graphics =
      get_queue_family_index(VK_QUEUE_GRAPHICS_BIT);
    VkDeviceQueueCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_info.queueFamilyIndex = queue_family_indices_.graphics;
    create_info.queueCount = 1;
    create_info.pQueuePriorities = &default_queue_priority;
    queue_create_infos.push_back(create_info);
  }

  const bool use_compute_queue = true;
  if (use_compute_queue) {
    queue_family_indices_.compute =
      get_queue_family_index(VK_QUEUE_COMPUTE_BIT);
    if (queue_family_indices_.compute != queue_family_indices_.graphics) {
      VkDeviceQueueCreateInfo create_info{};
      create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      create_info.queueFamilyIndex = queue_family_indices_.compute;
      create_info.queueCount = 1;
      create_info.pQueuePriorities = &default_queue_priority;
      queue_create_infos.push_back(create_info);
    }
  } else {
    queue_family_indices_.compute = queue_family_indices_.graphics;
  }

  const bool use_transfer_queue = true;
  if (use_transfer_queue) {
    queue_family_indices_.transfer =
      get_queue_family_index(VK_QUEUE_TRANSFER_BIT);
    if ((queue_family_indices_.transfer != queue_family_indices_.graphics) &&
        (queue_family_indices_.transfer != queue_family_indices_.compute)) {
      VkDeviceQueueCreateInfo create_info{};
      create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      create_info.queueFamilyIndex = queue_family_indices_.transfer;
      create_info.queueCount = 1;
      create_info.pQueuePriorities = &default_queue_priority;
      queue_create_infos.push_back(create_info);
    }
  } else {
    queue_family_indices_.transfer = queue_family_indices_.graphics;
  }

  std::vector<const char*> device_extensions(enabled_extensions);
  if (use_swap_chain) {
    device_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  }

  VkDeviceCreateInfo device_create_info{};
  device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_create_info.queueCreateInfoCount = queue_create_infos.size();
  device_create_info.pQueueCreateInfos = queue_create_infos.data();
  device_create_info.pEnabledFeatures = &enabled_features;

  VkPhysicalDeviceFeatures2 physical_device_features_2{};
  if (next_chain) {
    physical_device_features_2.sType =
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    physical_device_features_2.features = enabled_features;
    physical_device_features_2.pNext = next_chain;
    device_create_info.pEnabledFeatures = nullptr;
    device_create_info.pNext = &physical_device_features_2;
  }

  if (use_debug_markers) {
    device_extensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
  }

  if (!device_extensions.empty()) {
    for (auto extension : device_extensions) {
      // TODO: Check the extension is supported.
    }
    device_create_info.enabledExtensionCount = device_extensions.size();
    device_create_info.ppEnabledExtensionNames = device_extensions.data();
  }

  if (auto result = vkCreateDevice(
        physical_device_, &device_create_info, nullptr, &logical_device_);
      result != VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device");
  }

  VkCommandPoolCreateInfo command_pool_create_info{};
  command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  command_pool_create_info.queueFamilyIndex = queue_family_indices_.graphics;
  command_pool_create_info.flags =
    VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  VK_CHECK_RESULT(vkCreateCommandPool(
    logical_device_, &command_pool_create_info, nullptr, &command_pool_));
}

Device::~Device()
{
  if (command_pool_) {
    vkDestroyCommandPool(logical_device_, command_pool_, nullptr);
  }
  if (logical_device_) {
    vkDestroyDevice(logical_device_, nullptr);
  }
}

vk::Queue
Device::get_device_queue() const
{
  VkQueue queue;
  vkGetDeviceQueue(logical_device_, queue_family_indices_.graphics, 0, &queue);
  return queue;
}

vk::Format
Device::get_depth_format() const
{
  std::vector<vk::Format> formats = { vk::Format::eD32SfloatS8Uint,
                                      vk::Format::eD32Sfloat,
                                      vk::Format::eD24UnormS8Uint,
                                      vk::Format::eD16UnormS8Uint,
                                      vk::Format::eD16Unorm };

  for (auto& format : formats) {
    auto properties = physical_device_.getFormatProperties(format);
    if (properties.optimalTilingFeatures &
        vk::FormatFeatureFlagBits::eDepthStencilAttachment) {
      return format;
    }
  }

  throw std::runtime_error("could not find suitable depth format");
}

void
Device::connect_swap_chain(SwapChain& swap_chain, VkInstance instance)
{
  swap_chain.connect(instance, physical_device_, logical_device_);
}

vk::Semaphore
Device::create_semaphore(vk::SemaphoreCreateInfo& create_info)
{
  return logical_device_.createSemaphore(create_info);
}

std::uint32_t
Device::get_queue_family_index(vk::QueueFlags flags) const
{
  if (flags & vk::QueueFlagBits::eCompute) {
    for (auto i = 0ul; i < queue_family_properties_.size(); ++i) {
      if (auto i_flags = queue_family_properties_[i].queueFlags;
          (i_flags & flags) && (i_flags & vk::QueueFlagBits::eGraphics)) {
        return i;
      }
    }
  }

  if (flags & vk::QueueFlagBits::eTransfer) {
    for (auto i = 0ul; i < queue_family_properties_.size(); ++i) {
      if (auto i_flags = queue_family_properties_[i].queueFlags;
          (i_flags & flags) && (i_flags & vk::QueueFlagBits::eGraphics) &&
          (i_flags & vk::QueueFlagBits::eCompute)) {
        return i;
      }
    }
  }

  for (auto i = 0ul; i < queue_family_properties_.size(); ++i) {
    if (queue_family_properties_[i].queueFlags & flags) {
      return i;
    }
  }

  throw std::runtime_error("Could not find a matching queue family index");
}
