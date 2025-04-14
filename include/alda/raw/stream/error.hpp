//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_ERROR_HPP_INCLUDED
#define ALDA_RAW_STREAM_ERROR_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/raw/stream/error_fwd.hpp> // IWYU pragma: export
#include <alda/raw/stream/int_error.hpp>
#include <alda/raw/stream/stream_fail.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{
class error
{
public:
  // TODO(philipp): Add error types for arrays, etc.
  using variant = fcppt::variant::object<
    alda::raw::stream::stream_fail,
    alda::raw::stream::int_error>;

  ALDA_DETAIL_SYMBOL error(std::type_index, variant);

  [[nodiscard]] ALDA_DETAIL_SYMBOL std::type_index const &type() const;

  [[nodiscard]] ALDA_DETAIL_SYMBOL variant const &value() const;

  [[nodiscard]] ALDA_DETAIL_SYMBOL bool operator==(error const &) const;
private:
  std::type_index type_;
  variant value_;
};
}

#endif
