//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED
#define ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED

#include <alda/raw/detail/apply_binary.hpp>
#include <alda/raw/detail/dynamic_size.hpp>
#include <alda/raw/detail/is_static_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/if.hpp>
#include <brigand/functions/logical/and.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

template<
	typename Function,
	typename Size1,
	typename Size2
>
using
combine_static_sizes
=
typename
brigand::if_<
	brigand::and_<
		alda::raw::detail::is_static_size<
			Size1
		>,
		alda::raw::detail::is_static_size<
			Size2
		>
	>,
	alda::raw::detail::apply_binary<
		Function,
		Size1,
		Size2
	>,
	alda::raw::detail::dynamic_size
>::type;

}
}

#endif
