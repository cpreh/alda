//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED
#define ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED

#include <alda/raw/detail/dynamic_size.hpp>
#include <alda/raw/detail/is_static_size.hpp>
#include <fcppt/mpl/apply.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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
fcppt::mpl::apply<
	fcppt::mpl::if_<
		std::conjunction<
			alda::raw::detail::is_static_size<
				Size1
			>,
			alda::raw::detail::is_static_size<
				Size2
			>
		>,
		fcppt::mpl::bind<
			Function,
			fcppt::mpl::constant<
				Size1
			>,
			fcppt::mpl::constant<
				Size2
			>
		>,
		fcppt::mpl::constant<
			alda::raw::detail::dynamic_size
		>
	>
>;

}
}

#endif
