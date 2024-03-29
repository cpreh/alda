//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_NEEDED_SIZE_HPP_INCLUDED
#define ALDA_RAW_NEEDED_SIZE_HPP_INCLUDED

#include <alda/raw/dispatch_value.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/is_static_size.hpp>
#include <alda/raw/needed_size_static.hpp>
#include <alda/raw/size_type.hpp>
#include <fcppt/not.hpp>

namespace alda::raw
{

template <typename Type>
inline alda::raw::size_type needed_size(alda::raw::element_type<Type> const &)
  requires(alda::raw::is_static_size<Type>::value)
{
  return alda::raw::needed_size_static<Type>();
}

template <typename Type>
inline alda::raw::size_type needed_size(alda::raw::element_type<Type> const &_value)
  requires(fcppt::not_(alda::raw::is_static_size<Type>::value))
{
  return needed_size(alda::raw::dispatch_value<Type>(), _value);
}
}

#endif
