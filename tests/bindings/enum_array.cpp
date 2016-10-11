//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/enum_array.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/container/enum_array.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

enum class my_enum
{
	enum1,
	enum2,
	enum3,
	fcppt_maximum = enum3
};

typedef
unsigned
int_type;

typedef
fcppt::container::enum_array<
	my_enum,
	int_type
>
array;

typedef
alda::bindings::enum_array<
	array,
	alda::bindings::unsigned_<
		int_type,
		fcppt::endianness::format::little
	>
>
array_binding;


typedef
fcppt::either::object<
	alda::raw::stream::error,
	array
>
either_result_type;

}

BOOST_TEST_DONT_PRINT_LOG_VALUE(
	either_result_type
)

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_enum_array_stream
)
{
FCPPT_PP_POP_WARNING

	array const test(
		fcppt::algorithm::enum_array_init<
			array
		>(
			[](
				my_enum const _element
			)
			{
				return
					fcppt::cast::enum_to_int<
						int_type
					>(
						_element
					);
			}
		)
	);

	std::stringstream stream;

	alda::serialization::write<
		array_binding
	>(
		stream,
		test
	);

	BOOST_CHECK_EQUAL(
		alda::serialization::read<
			array_binding
		>(
			stream
		),
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			test
		)
	);
}
