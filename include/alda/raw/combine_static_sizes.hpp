//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED
#define ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED

#include <alda/raw/size_type.hpp>
#include <alda/raw/detail/dynamic_size.hpp>
#include <alda/raw/detail/from_number.hpp>
#include <alda/raw/detail/is_static_size.hpp>
#include <alda/raw/detail/to_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
alda::raw::detail::from_number<
	alda::raw::size_type,
	metal::invoke<
		metal::if_<
			fcppt::metal::to_number<
				std::conjunction<
					alda::raw::detail::is_static_size<
						Size1
					>,
					alda::raw::detail::is_static_size<
						Size2
					>
				>
			>,
			metal::bind<
				Function,
				metal::always<
					alda::raw::detail::to_number<
						Size1
					>
				>,
				metal::always<
					alda::raw::detail::to_number<
						Size2
					>
				>
			>,
			metal::always<
				alda::raw::detail::dynamic_size
			>
		>
	>
>;

}
}

#endif
