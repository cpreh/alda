//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STATIC_SIZE_HPP_INCLUDED
#define ALDA_RAW_STATIC_SIZE_HPP_INCLUDED

#include <alda/raw/static_size_impl.hpp>

namespace alda::raw
{

template <typename T>
using static_size = typename alda::raw::static_size_impl<T>::type;

}

#endif
