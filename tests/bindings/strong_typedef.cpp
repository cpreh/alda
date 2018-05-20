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
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/endianness/format.hpp>
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
either_result_type;

}

TEST_CASE(
	"bindings::strong_typedef",
	"[alda]"
)
{
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

	CHECK(
		alda::serialization::read<
			strong_binding
		>(
			stream
		)
		==
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			value
		)
	);
}
