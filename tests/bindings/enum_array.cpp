//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/enum_array.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/container/enum_array.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
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

}


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_enum_array
)
{
FCPPT_PP_POP_WARNING

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

	FCPPT_RECORD_MAKE_LABEL(
		array_label
	);

	typedef
	alda::raw::record_variadic<
		fcppt::record::element<
			array_label,
			array_binding
		>
	>
	message;

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

	message const msg(
		array_label{} =
			test
	);

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			array_label
		>(
			msg
		)[
			my_enum::enum1
		],
		0u
	);

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			array_label
		>(
			msg
		)[
			my_enum::enum2
		],
		1u
	);

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			array_label
		>(
			msg
		)[
			my_enum::enum3
		],
		2u
	);
}
