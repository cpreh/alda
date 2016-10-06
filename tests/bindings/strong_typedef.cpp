//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/strong_typedef.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
base_type;

FCPPT_MAKE_STRONG_TYPEDEF(
	base_type,
	strong_type
);

typedef
alda::bindings::strong_typedef<
	strong_type,
	alda::bindings::unsigned_<
		base_type,
		fcppt::endianness::format::little
	>
>
strong_binding;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	strong_type
>
result_type;

}

#if !defined(FCPPT_NARROW_STRING)
BOOST_TEST_DONT_PRINT_LOG_VALUE(
	result_type
)
#endif


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_strong_typedef_stream
)
{
FCPPT_PP_POP_WARNING

	strong_type const value{
		fcppt::literal<
			std::uint32_t
		>(
			42u
		)
	};

	std::stringstream stream;

	alda::serialization::write<
		strong_binding
	>(
		stream,
		value
	);

	BOOST_CHECK_EQUAL(
		alda::serialization::read<
			strong_binding
		>(
			stream
		),
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			value
		)
	);
}
