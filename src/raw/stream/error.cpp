#include <alda/raw/stream/error.hpp>
#include <fcppt/variant/comparison.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

alda::raw::stream::error::error(std::type_index const _type, variant _value)
    : type_{_type}, value_{_value}
{
}

std::type_index const &alda::raw::stream::error::type() const { return this->type_; }

alda::raw::stream::error::variant const &alda::raw::stream::error::value() const
{
  return this->value_;
}

bool alda::raw::stream::error::operator==(error const &) const = default;
