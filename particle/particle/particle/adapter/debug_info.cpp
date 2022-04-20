#include "particle/adapter/debug_info.hpp"

using namespace particle;

Field<>::Field(const std::string& label)
  : label_(label)
{}

Field<>::~Field() = default;

const std::string&
Field<>::label() const
{
  return label_;
}

const std::string
Field<>::to_string() const
{
  return label_;
}

bool
Field<>::is_static() const
{
  return false;
}

auto
DebugInfo::fields() -> fields_type&
{
  return fields_;
}
