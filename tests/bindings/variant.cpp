//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/signed.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
uint_type;

typedef
std::int16_t
int_type;

typedef
boost::mpl::vector2<
	uint_type,
	int_type
>
variant_types;

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
boost::mpl::vector2<
	alda::bindings::unsigned_<
		uint_type,
		endianness
	>,
	alda::bindings::signed_<
		int_type,
		endianness
	>
>
adapted_types;

typedef
alda::bindings::variant<
	variant_types,
	adapted_types
>
variant_binding;

typedef
fcppt::variant::object<
	variant_types
>
variant_type;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	variant_type
>
result_type;

}

#if !defined(FCPPT_NARROW_STRING)
BOOST_TEST_DONT_PRINT_LOG_VALUE(
	result_type
)
#endif

namespace
{

void
do_test(
	variant_type const &_value
)
{
	std::stringstream stream;

	alda::serialization::write<
		variant_binding
	>(
		stream,
		_value
	);

	BOOST_CHECK_EQUAL(
		alda::serialization::read<
			variant_binding
		>(
			stream
		),
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			_value
		)
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_variant_stream
)
{
FCPPT_PP_POP_WARNING

	do_test(
		variant_type{
			fcppt::literal<
				uint_type
			>(
				42u
			)
		}
	);

	do_test(
		variant_type{
			fcppt::literal<
				int_type
			>(
				13
			)
		}
	);
}
