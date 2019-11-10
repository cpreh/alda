//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_DETAIL_CONVERT_NUMBER_HPP_INCLUDED
#define ALDA_RAW_DETAIL_CONVERT_NUMBER_HPP_INCLUDED

#include <alda/raw/detail/dynamic_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/number/if.hpp>
#include <metal/number/number.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace detail
{

template<
	typename Type,
	typename Lambda
>
using
convert_number
=
metal::invoke<
	metal::if_<
		metal::number<
			std::is_same_v<
				Type,
				alda::raw::detail::dynamic_size
			>
		>,
		metal::always<
			alda::raw::detail::dynamic_size
		>,
		metal::bind<
			Lambda,
			metal::always<
				Type
			>
		>
	>
>;

}
}
}

#endif
