#include "particle/concepts.hpp"

#include <concepts>
#include <memory>
#include <string>
#include <vector>

namespace particle {

template<typename...>
class Field;

template<>
class Field<>
{
public:
  using type = Field;

  Field(const std::string& label);
  virtual ~Field();

  const std::string& label() const;
  virtual const std::string to_string() const;
  virtual bool is_static() const;

private:
  std::string label_;
};

struct Dynamic;
struct MinMax;
struct Static;

template<typename T>
class Field<Static, T> : public Field<>
{
public:
  using type = Field;
  using parent_type = Field<>;

  Field(const std::string& label, const T& value)
    : parent_type(label)
    , value_(value)
  {}

  ~Field() override = default;

  const std::string to_string() const override
  {
    return std::to_string(value_);
  }
  bool is_static() const { return true; }

private:
  T value_;
};

template<detail::arithmetic T>
class Field<MinMax, T> : public Field<>
{
public:
  using type = Field;
  using parent_type = Field<>;

  Field(const std::string& label, T& value)
    : parent_type(label)
    , value_(value)
    , min_(value)
    , max_(value)
  {}

  const std::string to_string() const override
  {
    T min, max = min_, max_;
    if (value_ > max_) {
      max = value_;
    }
    if (value_ < min_) {
      min = value_;
    }
    if (min_ == 0) {
      min = value_;
    }

    return "" + std::to_string(value_) + ":[" + std::to_string(min) + "/" +
           std::to_string(max) + "]";
  }

private:
  T value_;
  T min_;
  T max_;
};

class DebugInfo
{
public:
  using type = DebugInfo;
  using fields_type = std::vector<std::unique_ptr<Field<>>>;

  fields_type& fields();

  template<class T, typename A, typename... As>
  void insert(const std::string& label, A& a, As&&... as)
  {
    for (auto& field : fields_) {
      if (field->label() == label) {
        if (field->is_static()) {
          field = std::make_unique<Field<T, A, As...>>(
            label, a, std::forward<As>(as)...);
        }
      }
    }

    auto field =
      std::make_unique<Field<T, A, As...>>(label, a, std::forward<As>(as)...);
    fields_.push_back(std::move(field));
  }

private:
  fields_type fields_;
};

}
