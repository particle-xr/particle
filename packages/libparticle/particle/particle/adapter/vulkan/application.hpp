#include <cstdint>
#include <memory>
#include <string>

namespace particle::vulkan {

class Instance;
class Debugger;

class Application
{
public:
  using type = Application;

  Application(std::string name, int argc, char* argv[]);
  virtual ~Application();

  void run();

protected:
  Instance& instance();

private:
  std::unique_ptr<Instance> instance_;
  std::unique_ptr<Debugger> debugger_;
};

}
