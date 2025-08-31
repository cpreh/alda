//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_PLACE_AND_UPDATE_HPP_INCLUDED
#define ALDA_RAW_PLACE_AND_UPDATE_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

template <typename Type>
[[nodiscard]] inline alda::raw::pointer
place_and_update(alda::raw::element_type<Type> const &_value, alda::raw::pointer const _data)
{
  alda::raw::place<Type>(_value, _data);

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  return _data + alda::raw::needed_size<Type>(_value);
}

FCPPT_PP_POP_WARNING

}

#endif
