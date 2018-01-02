//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SMALLEST_UINT_HPP_INCLUDED
#define ALDA_SMALLEST_UINT_HPP_INCLUDED

#include <fcppt/brigand/numeric_max.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/comparison/greater_equal.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/front.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types/args.hpp>
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
brigand::front<
	brigand::find<
		brigand::list<
			std::uint8_t,
			std::uint16_t,
			std::uint32_t,
			std::uint64_t
		>,
		brigand::bind<
			brigand::greater_equal,
			brigand::bind<
				fcppt::brigand::numeric_max,
				brigand::_1
			>,
			std::integral_constant<
				std::size_t,
				Max
			>
		>
	>
>;

}

#endif
