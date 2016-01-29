//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	net_buffer_circular_receive
)
{
FCPPT_PP_POP_WARNING

	alda::net::buffer::circular_receive::object buffer{
		alda::net::buffer::max_receive_size{
			1u
		}
	};

	{
		alda::net::buffer::circular_receive::part const part(
			buffer.next_receive_part()
		);

		BOOST_REQUIRE_EQUAL(
			part.size(),
			1u
		);

		for(
			alda::net::value_type &elem
			:
			part
		)
			elem =
				fcppt::literal<
					alda::net::value_type
				>(
					1u
				);

		buffer.bytes_received(
			part.size()
		);
	}

	alda::net::buffer::circular_receive::object::joined_range const range(
		buffer.range()
	);

	BOOST_CHECK_EQUAL(
		range.size(),
		1u
	);

	for(
		alda::net::value_type const &elem
		:
		range
	)
		BOOST_CHECK_EQUAL(
			elem,
			fcppt::literal<
				alda::net::value_type
			>(
				1u
			)
		);
}
