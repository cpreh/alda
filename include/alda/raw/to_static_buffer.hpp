//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_TO_STATIC_BUFFER_HPP_INCLUDED
#define ALDA_RAW_TO_STATIC_BUFFER_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/static_buffer.hpp>
#include <fcppt/no_init.hpp>

namespace alda::raw
{

template <typename Type>
alda::raw::static_buffer<Type> to_static_buffer(alda::raw::element_type<Type> const &_value)
{
  alda::raw::static_buffer<Type> temp_buffer{fcppt::no_init{}};

  alda::raw::place<Type>(_value, temp_buffer.data());

  return temp_buffer;
}

}

#endif
