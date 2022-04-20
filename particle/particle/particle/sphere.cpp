#include "particle/sphere.hpp"

#include "particle/math.hpp"

using namespace particle;

Sphere::Sphere(Dimensional<3> origin, double radius)
  : origin_(origin)
  , vertices_(12 * 3)
{
  int i1, i2;
  float z, xy;
  float hAngle1 = -PI / 2 - H_ANGLE / 2;
  float hAngle2 = -PI / 2;

  vertices_[0] = 0;
  vertices_[1] = 0;
  vertices_[2] = radius;

  for (auto i = 1; i <= 5; ++i) {
    i1 = i * 3;
    i2 = (i + 5) * 3;

    z = radius * sinf(V_ANGLE);
    xy = radius * cosf(V_ANGLE);

    vertices_[i1] = xy * cosf(hAngle1);
    vertices_[i2] = xy * cosf(hAngle2);
    vertices_[i1 + 1] = xy * sinf(hAngle1);
    vertices_[i2 + 1] = xy * sinf(hAngle2);
    vertices_[i1 + 2] = z;
    vertices_[i2 + 2] = -z;

    hAngle1 += H_ANGLE;
    hAngle2 += H_ANGLE;
  }

  i1 = 11 * 3;
  vertices_[i1] = 0;
  vertices_[i1 + 1] = 0;
  vertices_[i1 + 2] = -radius;
}

const Dimensional<3>&
Sphere::origin()
{
  return origin_;
}
