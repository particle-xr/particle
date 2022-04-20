#include "particle/adapter/vulkan/debugger.hpp"
#include "particle/adapter/vulkan/utils.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vulkan/vulkan_core.h>

using namespace particle::vulkan;

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                            VkDebugUtilsMessageTypeFlagsEXT type,
                            const VkDebugUtilsMessengerCallbackDataEXT* data,
                            void* user_data)
{
  std::ostringstream message;

  message << vk::to_string(
               static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(severity))
          << ": "
          << vk::to_string(static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(type))
          << ":\n"
          << "\t"
          << "messageIdName: " << data->pMessageIdName << "\n"
          << "\t"
          << "messageIdNumber: " << data->messageIdNumber << "\n"
          << "\t"
          << "message: " << data->pMessage << "\n";

  if (data->queueLabelCount > 0) {
    message << "\t"
            << "Queue labels:\n";
    for (auto i = 0ul; i < data->queueLabelCount; ++i) {
      message << "\t\t"
              << "labelName: " << data->pQueueLabels[i].pLabelName << "\n";
    }
  }

  if (data->cmdBufLabelCount > 0) {
    message << "\t"
            << "CommandBuffer labels:\n";
    for (auto i = 0ul; i < data->cmdBufLabelCount; ++i) {
      message << "\t\t"
              << "labelName: " << data->pCmdBufLabels[i].pLabelName << "\n";
    }
  }

  if (data->objectCount > 0) {
    message << "\t"
            << "Objects:\n";
    for (auto i = 0ul; i < data->objectCount; ++i) {
      message << "\t\t"
              << "Object " << i << "\n";
      message << "\t\t\t"
              << "objectType: "
              << vk::to_string(
                   static_cast<vk::ObjectType>(data->pObjects[i].objectType))
              << "\n";
      message << "\t\t\t"
              << "objectHandle: " << data->pObjects[i].objectHandle << "\n";
      if (data->pObjects[i].pObjectName) {
        message << "\t\t\t"
                << "objectName: " << data->pObjects[i].pObjectName << "\n";
      }
    }

    std::cout << message.str() << std::endl;

    return false; // N.B. Don't abort.
  }
}

Debugger::Debugger(vk::Instance instance)
  : instance_(instance)
{
  vk::DebugUtilsMessengerCreateInfoEXT create_info{
    .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                       vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
    .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                   vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
    .pfnUserCallback = DebugUtilsMessengerCallback,
  };
  debug_messenger_ = instance.createDebugUtilsMessengerEXTUnique(create_info);
}

Debugger::~Debugger() = default;
