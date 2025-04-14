#ifndef ALDA_RAW_STREAM_INT_ERROR_KIND_TO_STRING_HPP_INCLUDED
#define ALDA_RAW_STREAM_INT_ERROR_KIND_TO_STRING_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/raw/stream/int_error_kind_fwd.hpp>
#include <fcppt/enum/to_string_impl_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

namespace fcppt::enum_
{
template <>
struct to_string_impl<alda::raw::stream::int_error_kind>
{
  ALDA_DETAIL_SYMBOL
  static std::string_view get(alda::raw::stream::int_error_kind);
};

}

#endif
