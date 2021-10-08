//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STATIC_SIZE_IMPL_HPP_INCLUDED
#define ALDA_RAW_STATIC_SIZE_IMPL_HPP_INCLUDED

#include <alda/raw/detail/dynamic_size.hpp>

namespace alda::raw
{

template <typename T>
struct static_size_impl
{
  using type = alda::raw::detail::dynamic_size;
};

}

#endif
