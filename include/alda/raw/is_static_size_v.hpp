//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_IS_STATIC_SIZE_V_HPP_INCLUDED
#define ALDA_RAW_IS_STATIC_SIZE_V_HPP_INCLUDED

#include <alda/raw/is_static_size.hpp>

namespace alda::raw
{

template <typename Type>
// NOLINTNEXTLINE(modernize-type-traits)
constexpr inline bool is_static_size_v = alda::raw::is_static_size<Type>::value;

}

#endif
