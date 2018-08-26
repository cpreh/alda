//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/array.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/defer.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <array>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::array<
	unsigned,
	2
>
int_array2;

typedef
alda::bindings::array<
	int_array2,
	alda::bindings::unsigned_<
		int_array2::value_type,
		fcppt::endianness::format::little
	>
>
array_binding;

static_assert(
	alda::raw::static_size<
		array_binding
	>::value
	==
	sizeof(
		unsigned
	)
	*
	2u,
	""
);

typedef
fcppt::either::object<
	alda::raw::stream::error,
	int_array2
>
either_result_type;

}

TEST_CASE(
	"bindings::array",
	"[alda]"
)
{
	int_array2 const test{{
		2u,
		5u
	}};

	std::stringstream stream{};

	alda::serialization::write<
		array_binding
	>(
		stream,
		test
	);

	CHECK(
		fcppt::catch_::defer(
			alda::serialization::read<
				array_binding
			>(
				stream
			)
			==
			fcppt::either::make_success<
				alda::raw::stream::error
			>(
				test
			)
		)
	);
}
