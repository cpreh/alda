//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/is_static_size.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/defer.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <sstream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
alda::bindings::unsigned_<
	std::uint16_t,
	endianness
>
length_binding;

typedef
alda::bindings::fundamental<
	unsigned
>
uint_binding;

typedef
std::vector<
	unsigned
>
uint_vector;

typedef
alda::bindings::dynamic_len<
	uint_vector,
	uint_binding,
	length_binding
>
dynamic_len_binding;

static_assert(
	!alda::raw::is_static_size<
		alda::raw::static_size<
			dynamic_len_binding
		>
	>::value,
	""
);

typedef
fcppt::either::object<
	alda::raw::stream::error,
	uint_vector
>
either_result_type;

}

TEST_CASE(
	"bindings::dynamic_len",
	"[alda]"
)
{
	uint_vector const vec{
		1,
		2
	};

	std::stringstream stream;

	alda::serialization::write<
		dynamic_len_binding
	>(
		stream,
		vec
	);

	either_result_type const result(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			dynamic_len_binding
		>(
			stream
		)
	);

	CHECK(
		fcppt::catch_::defer(
			result
			==
			either_result_type{
				vec
			}
		)
	);
}
