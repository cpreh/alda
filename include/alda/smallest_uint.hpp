//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SMALLEST_UINT_HPP_INCLUDED
#define ALDA_SMALLEST_UINT_HPP_INCLUDED

#include <fcppt/mpl/numeric_max.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstddef>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace alda
{

template<
	std::size_t Max
>
using
smallest_uint
=
typename
boost::mpl::deref<
	typename
	boost::mpl::find_if<
		boost::mpl::vector4<
			std::uint8_t,
			std::uint16_t,
			std::uint32_t,
			std::uint64_t
		>,
		boost::mpl::greater_equal<
			fcppt::mpl::numeric_max<
				boost::mpl::_1
			>,
			boost::mpl::integral_c<
				std::size_t,
				Max
			>
		>
	>::type
>::type;

};

#endif
