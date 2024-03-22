//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_NEEDED_SIZE_STATIC_HPP_INCLUDED
#define ALDA_RAW_NEEDED_SIZE_STATIC_HPP_INCLUDED

#include <alda/raw/is_static_size.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>

namespace alda::raw
{

template <typename Type>
constexpr alda::raw::size_type needed_size_static()
  requires(alda::raw::is_static_size<Type>::value)
{
  return alda::raw::static_size<Type>::value;
}

}

#endif
