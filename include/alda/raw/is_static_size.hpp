//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_IS_STATIC_SIZE_HPP_INCLUDED
#define ALDA_RAW_IS_STATIC_SIZE_HPP_INCLUDED

#include <alda/raw/static_size.hpp>
#include <alda/raw/detail/is_static_size.hpp>

namespace alda::raw
{

template <typename Type>
using is_static_size = alda::raw::detail::is_static_size<alda::raw::static_size<Type>>;

}

#endif
