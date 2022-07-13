#include "particle/world.hxx"

namespace particle {

World<2>::World(int height, int width)
  : height_(height)
  , width_(width)
  , center_({ (height / 2), (width / 2) })
{}

const Point<2>&
World<2>::center() const
{
  return center_;
}

}
