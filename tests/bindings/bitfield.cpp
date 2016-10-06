//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/bitfield.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/container/bitfield/comparison.hpp>
#include <fcppt/container/bitfield/object.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/endianness/format.hpp>
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
	alda_bitfield_stream
)
{
FCPPT_PP_POP_WARNING

	typedef
	fcppt::container::bitfield::object<
		unsigned,
		alda::raw::integral_size<
			64u
		>
	>
	bitfield;

	typedef
	alda::bindings::bitfield<
		bitfield,
		fcppt::endianness::format::little
	>
	bitfield_binding;

	bitfield test(
		bitfield::null()
	);

	test[
		42u
	] = true;

	std::stringstream stream;

	alda::serialization::write<
		bitfield_binding
	>(
		stream,
		test
	);

	BOOST_CHECK(
		alda::serialization::read<
			bitfield_binding
		>(
			stream
		)
		==
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			test
		)
	);
}
