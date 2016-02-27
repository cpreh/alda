//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/exception.hpp>
#include <alda/bindings/signed.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <limits>
#include <sstream>
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
int_binding;

bool
check_exception(
	alda::exception const &
)
{
	return
		true;
}

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

typedef
fcppt::either::object<
	alda::raw::stream::error,
	int_type
>
result_type;

void
test_conversion(
	int_type const _value
)
{
	std::stringstream stream;

	alda::serialization::write<
		int_binding
	>(
		stream,
		_value
	);

	result_type const result(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			int_binding
		>(
			stream
		)
	);

	BOOST_CHECK_EQUAL(
		result_type{
			_value
		},
		result
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_signed_stream
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
	{
		std::ostringstream stream;

		BOOST_CHECK_EXCEPTION(
			alda::serialization::write<
				int_binding
			>(
				stream,
				min
			),
			alda::exception,
			::check_exception
		);
	}
FCPPT_PP_POP_WARNING

}
