#pragma once

#include "vec3.hpp"

#include <iostream>

inline void
write_color(std::ostream& os, const color& pixel_color)
{
  os << static_cast<int>(255.999 * pixel_color.x()) << " "
     << static_cast<int>(255.999 * pixel_color.y()) << " "
     << static_cast<int>(255.999 * pixel_color.z()) << "\n";
}
