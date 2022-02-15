#include "particle/adapter/vulkan/instance.hpp"
#include "particle/adapter/vulkan/debug.hpp"

// #include <wayland-client.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using namespace particle::vulkan;

Instance::Instance(std::string name, bool enable_validation)
  : name_(name)
  , enable_validation_(enable_validation)
{
  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = name_.c_str();
  app_info.pEngineName = "particle";
  app_info.apiVersion = VK_API_VERSION_1_2;

  std::vector<const char*> extensions = { VK_KHR_SURFACE_EXTENSION_NAME };
  // extensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);

  std::uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
  if (extension_count > 0) {
    std::vector<VkExtensionProperties> supported_extensions(extension_count);
    if (vkEnumerateInstanceExtensionProperties(
          nullptr, &extension_count, &supported_extensions.front()) ==
        VK_SUCCESS) {
      for (auto extension : supported_extensions) {
        supported_extensions_.push_back(extension.extensionName);
      }
    }
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

  VkInstanceCreateInfo instance_create_info = {};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_create_info.pNext = nullptr;
  instance_create_info.pApplicationInfo = &app_info;
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
    std::uint32_t instance_layer_count;
    vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
    std::vector<VkLayerProperties> instance_layer_properties(
      instance_layer_count);
    vkEnumerateInstanceLayerProperties(&instance_layer_count,
                                       &instance_layer_properties.front());
    bool validation_layer_present = false;
    for (auto layer : instance_layer_properties) {
      if (strcmp(layer.layerName, validation_layer_name) == 0) {
        validation_layer_present = true;
        break;
      }
    }
    if (validation_layer_present) {
      instance_create_info.ppEnabledLayerNames = &validation_layer_name;
      instance_create_info.enabledLayerCount = 1;
    } else {
      std::cerr << "Validation layer is not present; validation is disabled"
                << std::endl;
      enable_validation_ = false;
    }
  }

  if (auto result =
        vkCreateInstance(&instance_create_info, nullptr, &instance_);
      result != VK_SUCCESS) {
    throw std::runtime_error("failed to create VkInstance (error code: " +
                             std::to_string(result) + ")");
  }
}

Instance::~Instance()
{
  if (enable_validation_) {
    // TODO: Destroy debug callback
  }

  vkDestroyInstance(instance_, nullptr);
}

void
Instance::operator()(Debugger& debugger)
{
  debugger.setup(instance_);
}

bool
Instance::validation_enabled() const
{
  return enable_validation_;
}
