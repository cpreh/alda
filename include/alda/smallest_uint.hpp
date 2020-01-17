//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SMALLEST_UINT_HPP_INCLUDED
#define ALDA_SMALLEST_UINT_HPP_INCLUDED

#include <fcppt/metal/to_number.hpp>
#include <fcppt/type_traits/numeric_max.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
metal::front<
	metal::remove_if<
		metal::list<
			std::uint8_t,
			std::uint16_t,
			std::uint32_t,
			std::uint64_t
		>,
		metal::bind<
			metal::lambda<
				metal::greater
			>,
			metal::always<
				fcppt::metal::to_number<
					std::integral_constant<
						std::size_t,
						Max
					>
				>
			>,
			metal::bind<
				metal::lambda<
					fcppt::metal::to_number
				>,
				metal::bind<
					metal::lambda<
						fcppt::type_traits::numeric_max
					>,
					metal::_1
				>
			>
		>
	>
>;

}

#endif
