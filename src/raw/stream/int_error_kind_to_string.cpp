#include <alda/raw/stream/int_error_kind.hpp>
#include <alda/raw/stream/int_error_kind_to_string.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

std::string_view fcppt::enum_::to_string_impl<alda::raw::stream::int_error_kind>::get(
    alda::raw::stream::int_error_kind const _kind)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch(_kind)
  {
  case alda::raw::stream::int_error_kind::invalid_bool:
    return "Invalid bool";
  case alda::raw::stream::int_error_kind::invalid_enum:
    return "Invalid enum";
  case alda::raw::stream::int_error_kind::invalid_variant_index:
    return "Invalid variant index";
  }
  FCPPT_PP_POP_WARNING
  throw fcppt::enum_::make_invalid(_kind);
}
