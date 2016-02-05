//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/smallest_uint.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


int
main()
{
	static_assert(
		std::is_same<
			alda::smallest_uint<
				20u
			>,
			std::uint8_t
		>::value,
		""
	);

	static_assert(
		std::is_same<
			alda::smallest_uint<
				256u
			>,
			std::uint16_t
		>::value,
		""
	);
}
