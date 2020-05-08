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
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/catch/variant.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/variant/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <catch2/catch.hpp>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

using
uint_type
=
std::uint32_t;

using
int_type
=
std::int16_t;

using
variant_types
=
metal::list<
	uint_type,
	int_type
>;

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

using
adapted_types
=
metal::list<
	alda::bindings::unsigned_<
		uint_type,
		endianness
	>,
	alda::bindings::signed_<
		int_type,
		endianness
	>
>;

using
variant_binding
=
alda::bindings::variant<
	variant_types,
	adapted_types
>;

using
variant_type
=
fcppt::variant::from_list<
	variant_types
>;

}

namespace
{

void
do_test(
	variant_type const &_value
)
{
	// NOLINTNEXTLINE(fuchsia-default-arguments-calls)
	std::stringstream stream{};

	alda::serialization::write<
		variant_binding
	>(
		stream,
		_value
	);

	CHECK(
		alda::serialization::read<
			variant_binding
		>(
			stream
		)
		==
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			_value
		)
	);
}

}

TEST_CASE(
	"bindings::variant",
	"[alda]"
)
{
	do_test(
		variant_type{
			fcppt::literal<
				uint_type
			>(
				42U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		}
	);

	do_test(
		variant_type{
			fcppt::literal<
				int_type
			>(
				13 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		}
	);
}
