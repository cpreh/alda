//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_PLACE_HPP_INCLUDED
#define ALDA_RAW_PLACE_HPP_INCLUDED

#include <alda/raw/dispatch_value.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/pointer.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

template <typename Type>
inline void place(alda::raw::element_type<Type> const &_value, alda::raw::pointer const _data)
{
  return place(alda::raw::dispatch_value<Type>(), _value, _data);
}

FCPPT_PP_POP_WARNING

}

#endif
