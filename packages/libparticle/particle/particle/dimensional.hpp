#include "particle/concepts.hpp"

namespace particle {

template<class T>
class X
{
public:
  using type = X;
  using value_type = T;

  X(const T& value)
    : value_(value)
  {}

  const T& x() { return value_; }

private:
  T value_;
};

template<class T>
class Y
{
public:
  using type = Y;
  using value_type = T;

  Y(const T& value)
    : value_(value)
  {}

  const T& y() { return value_; }

private:
  T value_;
};

template<class T>
class Z
{
public:
  using type = Z;
  using value_type = T;

  Z(const T& value)
    : value_(value)
  {}

  const T& z() { return value_; }

private:
  T value_;
};

template<int Dimensionality, class T = int>
class Dimensional;

template<class T>
class Dimensional<2, T>
  : public X<T>
  , public Y<T>
{
public:
  using type = Dimensional;

  Dimensional(const T& x, const T& y)
    : X<T>(x)
    , Y<T>(y)
  {}
};

template<class T>
class Dimensional<3, T>
  : public X<T>
  , public Y<T>
  , public Z<T>
{
public:
  using type = Dimensional;

  Dimensional(const T& x, const T& y, const T& z)
    : X<T>(x)
    , Y<T>(y)
    , Z<T>(z)
  {}
};

}
