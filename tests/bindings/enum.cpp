//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/enum.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/defer.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace
{

enum class test_enum
{
	value0,
	value1,
	fcppt_maximum = value1
};

typedef
alda::bindings::enum_<
	test_enum,
	alda::bindings::unsigned_<
		std::uint8_t,
		fcppt::endianness::format::little
	>
>
enum_binding;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	test_enum
>
either_result_type;

}

TEST_CASE(
	"bindings::enum",
	"[alda]"
)
{
	std::stringstream stream{};

	alda::serialization::write<
		enum_binding
	>(
		stream,
		test_enum::value1
	);

	either_result_type const result(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			enum_binding
		>(
			stream
		)
	);

	CHECK(
		fcppt::catch_::defer(
			result
			==
			either_result_type{
				test_enum::value1
			}
		)
	);

	stream.str(
		"\x15"
	);

	CHECK(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			enum_binding
		>(
			stream
		).has_failure()
	);
}
