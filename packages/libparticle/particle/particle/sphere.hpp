#include <vector>

namespace particle {

class Sphere
{
public:
  using type = Sphere;

  Sphere(double radius);

private:
  std::vector<float> vertices_;
};

}
