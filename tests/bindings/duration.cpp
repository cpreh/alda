//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/duration.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <ratio>
#include <sstream>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_duration_stream
)
{
FCPPT_PP_POP_WARNING

	typedef
	alda::bindings::unsigned_<
		std::uint32_t,
		fcppt::endianness::format::little
	>
	int_binding;

	typedef
	alda::bindings::duration<
		int_binding,
		std::milli
	>
	duration_binding;

	static_assert(
		alda::raw::static_size<
			duration_binding
		>::value
		==
		alda::raw::static_size<
			int_binding
		>::value,
		""
	);

	typedef
	alda::raw::element_type<
		duration_binding
	>
	duration;

	std::stringstream stream;

	alda::serialization::write<
		duration_binding
	>(
		stream,
		duration{
			10u
		}
	);

	BOOST_CHECK(
		alda::serialization::read<
			duration_binding
		>(
			stream
		)
		==
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			duration{
				10u
			}
		)
	);
}
