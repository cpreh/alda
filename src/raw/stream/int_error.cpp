#include <alda/raw/stream/int_error.hpp>
#include <alda/raw/stream/int_error_kind.hpp>

alda::raw::stream::int_error::int_error(
    alda::raw::stream::int_error_kind const _kind, type const _value)
    : kind_{_kind}, value_{_value}
{
}

alda::raw::stream::int_error_kind alda::raw::stream::int_error::kind() const { return this->kind_; }

alda::raw::stream::int_error::type alda::raw::stream::int_error::value() const
{
  return this->value_;
}

bool alda::raw::stream::int_error::operator==(int_error const &) const = default;
