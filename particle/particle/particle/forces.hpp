#pragma once

#include <utility>

namespace particle {

template<typename...>
class Force;

template<typename...>
class Forces;

template<>
class Forces<>
{};

template<typename F, typename... Fs>
class Forces<F, Fs...>
  : public Forces<Fs...>
  , public Force<F>
{
public:
  using type = Forces;
  using parent_type = Forces<Fs...>;

  template<typename U, typename... Us>
  Forces(U&& u, Us&&... us)
    : parent_type(std::forward<Us>(us)...)
    , Force<F>(std::forward<U>(u))
  {}

  /// Apply forces to T
  template<typename T>
  void operator()(T& t) const
  {
    as<F>()(t);
    (as<Fs>()(t), ...);
  }

private:
  template<typename T>
  const Force<T>& as() const
  {
    return *this;
  }
};

}
