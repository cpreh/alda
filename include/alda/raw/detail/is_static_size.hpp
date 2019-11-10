//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_DETAIL_IS_STATIC_SIZE_HPP_INCLUDED
#define ALDA_RAW_DETAIL_IS_STATIC_SIZE_HPP_INCLUDED

#include <alda/raw/detail/dynamic_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace detail
{

template<
	typename Size
>
using
is_static_size
=
std::negation<
	std::is_same<
		alda::raw::detail::dynamic_size,
		Size
	>
>;

}
}
}

#endif
