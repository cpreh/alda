//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/static.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

using
int_vec2
=
fcppt::math::vector::static_<
	unsigned,
	2
>;

using
vector_binding
=
alda::bindings::static_<
	int_vec2,
	alda::bindings::unsigned_<
		int_vec2::value_type,
		fcppt::endianness::format::little
	>
>;

static_assert(
	alda::raw::static_size<
		vector_binding
	>::type::value
	==
	sizeof(
		unsigned
	)
	*
	2U
);

using
either_result_type
=
fcppt::either::object<
	alda::raw::stream::error,
	int_vec2
>;

}

TEST_CASE(
	"bindings::static",
	"[alda]"
)
{
	int_vec2 const test(
		2U,
		5U
	);

	// NOLINTNEXTLINE(fuchsia-default-arguments-calls)
	std::stringstream stream{};

	alda::serialization::write<
		vector_binding
	>(
		stream,
		test
	);

	CHECK(
		alda::serialization::read<
			vector_binding
		>(
			stream
		)
		==
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			test
		)
	);
}
