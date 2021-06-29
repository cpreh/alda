//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SMALLEST_UINT_HPP_INCLUDED
#define ALDA_SMALLEST_UINT_HPP_INCLUDED

#include <fcppt/cast/size_fun.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/greater.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/front.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/remove_if.hpp>
#include <fcppt/type_traits/integral_cast.hpp>
#include <fcppt/type_traits/numeric_max.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{

template<
	std::size_t Max
>
using
smallest_uint
=
fcppt::mpl::list::front<
	fcppt::mpl::list::remove_if<
		fcppt::mpl::list::object<
			std::uint8_t,
			std::uint16_t,
			std::uint32_t,
			std::uint64_t
		>,
		fcppt::mpl::bind<
			fcppt::mpl::lambda<
				fcppt::mpl::greater
			>,
			fcppt::mpl::constant<
				std::integral_constant<
					std::size_t,
					Max
				>
			>,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					fcppt::type_traits::integral_cast
				>,
				fcppt::mpl::constant<
					std::size_t
				>,
				fcppt::mpl::constant<
					fcppt::cast::size_fun
				>,
				fcppt::mpl::bind<
					fcppt::mpl::lambda<
						fcppt::type_traits::numeric_max
					>,
					fcppt::mpl::arg<1>
				>
			>
		>
	>
>;

}

#endif
