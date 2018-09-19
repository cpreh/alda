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
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <catch2/catch.hpp>
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
brigand::list<
	uint_type,
	int_type
>
variant_types;

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
brigand::list<
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

}

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
