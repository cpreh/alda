//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/exception.hpp>
#include <alda/bindings/signed.hpp>
#include <alda/raw/record_variadic.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <limits>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::int16_t
int_type;

typedef
alda::bindings::signed_<
	int_type,
	fcppt::endianness::format::little
>
int_alda_type;

MAJUTSU_MAKE_ROLE_TAG(
	int_role
);

typedef
alda::raw::record_variadic<
	majutsu::role<
		int_alda_type,
		int_role
	>
>
message;

bool
check_exception(
	alda::exception const &
)
{
	return
		true;
}

void
test_conversion(
	int_type const _value
)
{
	message const msg(
		int_role{} =
			_value
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			int_role
		>(
			msg
		),
		_value
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_signed
)
{
FCPPT_PP_POP_WARNING

	test_conversion(
		fcppt::literal<
			int_type
		>(
			0
		)
	);

	test_conversion(
		fcppt::literal<
			int_type
		>(
			1337
		)
	);

	test_conversion(
		fcppt::literal<
			int_type
		>(
			-1337
		)
	);

	int_type const max(
		std::numeric_limits<
			int_type
		>::max()
	);

	int_type const min(
		std::numeric_limits<
			int_type
		>::min()
	);

	test_conversion(
		max
	);

	test_conversion(
		fcppt::literal<
			int_type
		>(
			-max
		)
	);

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4127)
	if(
		min
		+
		max
		<
		0
	)
		BOOST_CHECK_EXCEPTION(
			test_conversion(
				min
			),
			alda::exception,
			::check_exception
		);
FCPPT_PP_POP_WARNING

}
