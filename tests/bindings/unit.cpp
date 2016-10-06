//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/unit.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_unit_stream
)
{
FCPPT_PP_POP_WARNING

	std::stringstream stream;

	alda::serialization::write<
		alda::bindings::unit
	>(
		stream,
		fcppt::unit{}
	);

	BOOST_REQUIRE(
		stream.str().empty()
	);

	BOOST_CHECK(
		alda::serialization::read<
			alda::bindings::unit
		>(
			stream
		).has_success()
	);
}
