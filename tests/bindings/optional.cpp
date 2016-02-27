//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/optional.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/output.hpp>
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

typedef
fcppt::optional::object<
	base_type
>
optional_type;

typedef
alda::bindings::optional<
	base_type,
	alda::bindings::unsigned_<
		base_type,
		fcppt::endianness::format::little
	>
>
optional_binding;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	optional_type
>
result_type;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_optional_stream
)
{
FCPPT_PP_POP_WARNING

	{
		std::stringstream stream;

		alda::serialization::write<
			optional_binding
		>(
			stream,
			optional_type{
				42u
			}
		);

		result_type const result(
			alda::raw::make_generic<
				alda::raw::stream::istream,
				optional_binding
			>(
				stream
			)
		);

		BOOST_CHECK_EQUAL(
			result,
			result_type{
				optional_type{
					42u
				}
			}
		);
	}

	{
		std::stringstream stream;

		alda::serialization::write<
			optional_binding
		>(
			stream,
			optional_type{}
		);

		result_type const result(
			alda::raw::make_generic<
				alda::raw::stream::istream,
				optional_binding
			>(
				stream
			)
		);

		BOOST_CHECK_EQUAL(
			result,
			result_type{
				optional_type{}
			}
		);
	}
}
