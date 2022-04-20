#include "particle/adapter/vulkan/instance.hpp"
#include "particle/adapter/vulkan/debugger.hpp"
#include "particle/adapter/vulkan/device.hpp"
#include "particle/adapter/vulkan/su/utils.hpp"
#include "particle/adapter/vulkan/utils.hpp"

// #include <wayland-client.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using namespace particle::vulkan;

Instance::Instance(std::string name, bool enable_validation)
  : name_(name)
  , validation_enabled_(enable_validation)
{
  vk::ApplicationInfo app_info{ .pApplicationName = name.c_str(),
                                .pEngineName = "particle",
                                .apiVersion = VK_API_VERSION_1_2 };

  std::vector<const char*> extensions = { VK_KHR_SURFACE_EXTENSION_NAME };
  // extensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);

  auto supported_extensions = vk::enumerateInstanceExtensionProperties();
  for (auto extension : supported_extensions) {
    supported_extensions_.push_back(extension.extensionName);
  }

  if (!requested_extensions_.empty()) {
    for (auto extension : requested_extensions_) {
      if (std::find(supported_extensions_.begin(),
                    supported_extensions_.end(),
                    extension) == supported_extensions_.end()) {
        std::cerr << "Requested instance extension \"" << extension
                  << "\" is not supported" << std::endl;
      } else {
        extensions.push_back(extension);
      }
    }
  }

  vk::InstanceCreateInfo instance_create_info{ .pApplicationInfo = &app_info };

  if (!extensions.empty()) {
    if (enable_validation) {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    instance_create_info.enabledExtensionCount = extensions.size();
    instance_create_info.ppEnabledExtensionNames = extensions.data();
  }

  // TODO: Figure out why this isn't hitting.
  const auto validation_layer_name = "VK_LAYER_KHRONOS_validation";
  if (enable_validation) {
    auto supported_layers =
      vk::enumerateInstanceLayerProperties("VK_LAYER_KHRONOS_validation");
    if (supported_layers.empty()) {
      std::cerr << "Validation layer is not present; validation is disabled"
                << std::endl;
      validation_enabled_ = false;
    } else {
      instance_create_info.ppEnabledLayerNames = &validation_layer_name;
      instance_create_info.enabledLayerCount = 1;
    }
  }

  instance_ = vk::createInstanceUnique(instance_create_info, nullptr);

  if (validation_enabled_) {
    // debugger_ = std::make_unique<Debugger>(instance_);
  }

  physical_device_ = instance().enumeratePhysicalDevices().front();

  std::uint32_t graphics_queue_family_index = su::findGraphicsQueueFamilyIndex(
    physical_device_.getQueueFamilyProperties());

  std::uint32_t width, height = 64;
  su::WindowData window = su::createWindow(name, { width, height });
  vk::SurfaceKHR surface;
  {
    VkSurfaceKHR s;
    glfwCreateWindowSurface(
      static_cast<VkInstance>(instance()), window.handle, nullptr, &s);
    surface = vk::SurfaceKHR(s);
  }

  auto queue_family_properties = physical_device_.getQueueFamilyProperties();
  std::size_t present_queue_family_index =
    physical_device_.getSurfaceSupportKHR(graphics_queue_family_index, surface)
      ? graphics_queue_family_index
      : queue_family_properties.size();

  if (present_queue_family_index == queue_family_properties.size()) {
    for (auto i = 0ul; i < queue_family_properties.size(); ++i) {
      if ((queue_family_properties[i].queueFlags &
           vk::QueueFlagBits::eGraphics) &&
          physical_device_.getSurfaceSupportKHR(i, surface)) {
        graphics_queue_family_index = su::checked_cast<std::uint32_t>(i);
        present_queue_family_index = i;
        break;
      }
    }
    if (present_queue_family_index == queue_family_properties.size()) {
      for (auto i = 0ul; i < queue_family_properties.size(); ++i) {
        if (physical_device_.getSurfaceSupportKHR(i, surface)) {
          present_queue_family_index = i;
          break;
        }
      }
    }
    if ((graphics_queue_family_index == queue_family_properties.size()) ||
        (present_queue_family_index == queue_family_properties.size())) {
      throw std::runtime_error(
        "Could find a queue for graphics or present -> terminating");
    }
  }

  logical_device_ = utils::createDeviceUnique(
    physical_device_, graphics_queue_family_index, su::getDeviceExtensions());

  auto formats = physical_device_.getSurfaceFormatsKHR(surface);
  assert(!formats.empty());

  auto format = (formats.front().format == vk::Format::eUndefined
                   ? vk::Format::eB8G8R8A8Unorm
                   : formats.front().format);

  command_pool_ = device().createCommandPoolUnique(vk::CommandPoolCreateInfo{
    .flags = vk::CommandPoolCreateFlags(),
    .queueFamilyIndex = graphics_queue_family_index });

  command_buffer_ =
    std::move(device()
                .allocateCommandBuffersUnique(vk::CommandBufferAllocateInfo{
                  .commandPool = *command_pool_,
                  .level = vk::CommandBufferLevel::ePrimary,
                  .commandBufferCount = 1 })
                .front());
}

Instance::~Instance() = default;

bool
Instance::validation_enabled() const
{
  return validation_enabled_;
}

vk::Instance
Instance::instance()
{
  return *instance_;
}

vk::Device
Instance::device()
{
  return *logical_device_;
}
