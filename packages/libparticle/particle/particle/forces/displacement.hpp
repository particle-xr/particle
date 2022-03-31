#pragma once

#include "particle/forces.hpp"

namespace particle {

struct X;
struct Y;

namespace detail {

template<typename T>
concept displaceable_x = requires(T&& t)
{
  t.template displace<X>(10);
};

template<typename T>
concept displaceable_y = requires(T&& t)
{
  t.template displace<Y>(10);
};

template<typename T>
concept displaceable = displaceable_x<T> && displaceable_y<T>;

}

template<typename D>
class Displacement
{
public:
  using type = Displacement;
  using dimension = D;

  Displacement(double f)
    : force_(f)
  {}

  template<detail::displaceable T>
  void operator()(T& t) const
  {
    t.template displace<D>(force_);
  }

private:
  const double force_;
};

template<typename D>
class Force<Displacement<D>> : private Displacement<D>
{
public:
  using type = Force;
  using parent_type = Displacement<D>;

  Force(double f)
    : parent_type(f)
  {}

  template<typename T>
  void operator()(T& t) const
  {
    const parent_type& p = *this;
    (p)(t);
  }
};

}
