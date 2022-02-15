#pragma once

#include <vulkan/vulkan.h>

namespace particle::vulkan {

class Debugger
{
public:
  using type = Debugger;

  Debugger(VkDebugReportFlagsEXT flags, VkDebugReportCallbackEXT callback);
  ~Debugger();

  void setup(VkInstance instance);

private:
  VkDebugReportFlagsEXT flags_;
  VkDebugReportCallbackEXT callback_;
  PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT_;
  PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT_;
  VkInstance instance_;
  VkDebugUtilsMessengerEXT debug_utils_messenger_;
};

}
