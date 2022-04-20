#pragma once

#include "particle/concepts.hpp"

#include <iostream>

namespace particle {

class X
{
public:
  using type = X;

  X(double value)
    : value_(value)
  {}

  const double& x() const { return value_; }

  type& operator+=(const type& p) { return (value_ += p.x(), *this); }

  friend std::ostream& operator<<(std::ostream& os, const type& t)
  {
    return os << t.value_;
  }

  friend bool operator==(const type& lhs, const type& rhs)
  {
    return lhs.value_ == rhs.value_;
  }

  friend bool operator!=(const type& lhs, const type& rhs)
  {
    return !(lhs == rhs);
  }

private:
  double value_;
};

class Y
{
public:
  using type = Y;

  Y(const double& value)
    : value_(value)
  {}

  const double& y() const { return value_; }

  type& operator+=(const type& p) { return (value_ += p.y(), *this); }

  friend std::ostream& operator<<(std::ostream& os, const type& t)
  {
    return os << t.value_;
  }

  friend bool operator==(const type& lhs, const type& rhs)
  {
    return lhs.value_ == rhs.value_;
  }

  friend bool operator!=(const type& lhs, const type& rhs)
  {
    return !(lhs == rhs);
  }

private:
  double value_;
};

class Z
{
public:
  using type = Z;

  Z(double value)
    : value_(value)
  {}

  const double& z() const { return value_; }

  type& operator+=(const type& p) { return (value_ += p.z(), *this); }

  friend std::ostream& operator<<(std::ostream& os, const type& t)
  {
    return os << t.value_;
  }

  friend bool operator==(const type& lhs, const type& rhs)
  {
    return lhs.value_ == rhs.value_;
  }

  friend bool operator!=(const type& lhs, const type& rhs)
  {
    return !(lhs == rhs);
  }

private:
  double value_;
};

template<int Dimensionality>
class Dimensional;

template<>
class Dimensional<2>
  : public X
  , public Y
{
public:
  using type = Dimensional;

  Dimensional(const double& x, const double& y)
    : X(x)
    , Y(y)
  {}

  friend bool operator==(const type& lhs, const type& rhs)
  {
    return static_cast<const X&>(lhs) == static_cast<const X&>(rhs) &&
           static_cast<const Y&>(lhs) == static_cast<const Y&>(rhs);
  }

  friend bool operator!=(const type& lhs, const type& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename D>
  void displace(const auto& f)
  {
    D& d = *this;
    d += f;
  }
};

template<>
class Dimensional<3>
  : public X
  , public Y
  , public Z
{
public:
  using type = Dimensional;

  Dimensional(const double& x, const double& y, const double& z)
    : X(x)
    , Y(y)
    , Z(z)
  {}

  friend bool operator==(const type& lhs, const type& rhs)
  {
    return static_cast<const X&>(lhs) == static_cast<const X&>(rhs) &&
           static_cast<const Y&>(lhs) == static_cast<const Y&>(rhs) &&
           static_cast<const Z&>(lhs) == static_cast<const Z&>(rhs);
  }

  friend bool operator!=(const type& lhs, const type& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename D>
  void displace(const auto& f)
  {
    D& d = *this;
    d += f;
  }
};

}
