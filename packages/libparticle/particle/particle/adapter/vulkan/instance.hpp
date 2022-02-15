#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace particle::vulkan {

class Debugger;

class Instance
{
public:
  using type = Instance;

  Instance(std::string name, bool enable_validation);
  ~Instance();

  void operator()(Debugger&);

  bool validation_enabled() const;

private:
  std::string name_;
  bool enable_validation_ = false;
  std::vector<const char*> supported_extensions_;
  std::vector<const char*> requested_extensions_;
  VkInstance instance_;
};

}
