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
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <bit>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

using
base_type
=
std::uint32_t;

FCPPT_MAKE_STRONG_TYPEDEF(
	base_type,
	strong_type
);

using
strong_binding
=
alda::bindings::strong_typedef<
	strong_type,
	alda::bindings::unsigned_<
		base_type,
		std::endian::little
	>
>;

using
either_result_type
=
fcppt::either::object<
	alda::raw::stream::error,
	strong_type
>;

}

FCPPT_CATCH_BEGIN

TEST_CASE(
	"bindings::strong_typedef",
	"[alda]"
)
{
	strong_type const value{
		fcppt::literal<
			std::uint32_t
		>(
			42U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		)
	};

	// NOLINTNEXTLINE(fuchsia-default-arguments-calls)
	std::stringstream stream{};

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

FCPPT_CATCH_END
