#include "particle/adapter/vulkan/debugger.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace particle::vulkan;

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                            VkDebugUtilsMessageTypeFlagsEXT type,
                            const VkDebugUtilsMessengerCallbackDataEXT* data,
                            void* user_data)
{
  std::string prefix = "";
  if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    prefix = "VERBOSE: ";
  } else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    prefix = "INFO: ";
  } else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    prefix = "WARN: ";
  } else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    prefix = "ERROR: ";
  }

  std::stringstream message;
  message << prefix << "[" << data->messageIdNumber << ":"
          << data->pMessageIdName << "]: " << data->pMessage;
  if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    std::cerr << message.str() << std::endl;
  } else {
    std::cout << message.str() << std::endl;
  }

  return VK_FALSE; // N.B. Don't abort.
}

Debugger::Debugger(VkDebugReportFlagsEXT flags,
                   VkDebugReportCallbackEXT callback)
  : flags_(flags)
  , callback_(callback)
{}

Debugger::~Debugger()
{
  vkDestroyDebugUtilsMessengerEXT_(instance_, debug_utils_messenger_, nullptr);
}

void
Debugger::setup(VkInstance instance)
{
  vkCreateDebugUtilsMessengerEXT_ =
    reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
      vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
  vkDestroyDebugUtilsMessengerEXT_ =
    reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
      vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

  VkDebugUtilsMessengerCreateInfoEXT create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
  create_info.pfnUserCallback = DebugUtilsMessengerCallback;
  auto result = vkCreateDebugUtilsMessengerEXT_(
    instance, &create_info, nullptr, &debug_utils_messenger_);
  assert(result == VK_SUCCESS);

  instance_ = instance;
}
