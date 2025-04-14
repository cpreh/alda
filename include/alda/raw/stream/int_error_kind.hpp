//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_INT_ERROR_KIND_HPP_INCLUDED
#define ALDA_RAW_STREAM_INT_ERROR_KIND_HPP_INCLUDED

#include <alda/raw/stream/int_error_kind_fwd.hpp> // IWYU pragma: export
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{
enum class int_error_kind : std::uint8_t
{
  invalid_bool,
  invalid_enum,
  invalid_variant_index
};
}

FCPPT_ENUM_DEFINE_MAX_VALUE(alda::raw::stream::int_error_kind::invalid_variant_index)

#endif
