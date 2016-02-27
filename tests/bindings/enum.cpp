//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/enum.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace
{

enum class test_enum
{
	value0,
	value1,
	fcppt_maximum = value1
};

typedef
alda::bindings::enum_<
	test_enum,
	alda::bindings::unsigned_<
		std::uint8_t,
		fcppt::endianness::format::little
	>
>
enum_binding;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	test_enum
>
result_type;

}

BOOST_TEST_DONT_PRINT_LOG_VALUE(
	result_type
)

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_enum_stream
)
{
FCPPT_PP_POP_WARNING

	std::stringstream stream;

	alda::serialization::write<
		enum_binding
	>(
		stream,
		test_enum::value1
	);

	result_type const result(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			enum_binding
		>(
			stream
		)
	);

	BOOST_CHECK_EQUAL(
		result,
		result_type{
			test_enum::value1
		}
	);

	stream.str(
		"\x15"
	);

	BOOST_CHECK((
		alda::raw::make_generic<
			alda::raw::stream::istream,
			enum_binding
		>(
			stream
		).has_failure()
	));
}
