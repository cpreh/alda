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
#include <fcppt/catch/either.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch.hpp>
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
either_result_type;

}

TEST_CASE(
	"bindings::optiona",
	"[alda]"
)
{
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

		either_result_type const result(
			alda::raw::make_generic<
				alda::raw::stream::istream,
				optional_binding
			>(
				stream
			)
		);

		CHECK(
			result
			==
			either_result_type{
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

		either_result_type const result(
			alda::raw::make_generic<
				alda::raw::stream::istream,
				optional_binding
			>(
				stream
			)
		);

		CHECK(
			result
			==
			either_result_type{
				optional_type{}
			}
		);
	}
}
