//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/array.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/serialization/write.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/record_variadic.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/istream.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <array>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::array<
	unsigned,
	2
>
int_array2;

typedef
alda::bindings::array<
	int_array2,
	alda::bindings::unsigned_<
		int_array2::value_type,
		fcppt::endianness::format::little
	>
>
array_binding;

MAJUTSU_MAKE_ROLE_TAG(
	array_role
);

typedef
alda::raw::record_variadic<
	majutsu::role<
		array_binding,
		array_role
	>
>
message;

static_assert(
	alda::raw::static_size<
		array_binding
	>::value
	==
	sizeof(
		unsigned
	)
	*
	2u,
	""
);

static_assert(
	alda::raw::static_size<
		array_binding
	>::value
	==
	alda::raw::static_size<
		message
	>::value,
	""
);

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_array
)
{
FCPPT_PP_POP_WARNING

	int_array2 const test{{
		2u,
		5u
	}};

	BOOST_CHECK(
		majutsu::get<
			array_role
		>(
			message{
				array_role{} =
					test
			}
		)
		==
		test
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_array_stream
)
{
FCPPT_PP_POP_WARNING

	int_array2 const test{{
		2u,
		5u
	}};

	std::stringstream stream;

	alda::serialization::write(
		stream,
		message{
			array_role{} =
				test
		}
	);

	typedef
	fcppt::optional::object<
		message
	>
	optional_result;

	optional_result const result(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			message
		>(
			stream
		)
	);

	BOOST_REQUIRE(
		result.has_value()
	);

	BOOST_CHECK(
		majutsu::get<
			array_role
		>(
			result.get_unsafe()
		)
		==
		test
	);
}
