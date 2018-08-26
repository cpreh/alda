//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/bitfield.hpp>
#include <alda/raw/data.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/brigand/ceil_div.hpp>
#include <fcppt/catch/defer.hpp>
#include <fcppt/container/bitfield/comparison.hpp>
#include <fcppt/container/bitfield/object.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <limits>
#include <sstream>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"bindings::bitfield",
	"[alda]"
)
{
	typedef
	fcppt::container::bitfield::object<
		unsigned,
		alda::raw::integral_size<
			64u
		>
	>
	bitfield;

	typedef
	alda::bindings::bitfield<
		bitfield,
		fcppt::endianness::format::little
	>
	bitfield_binding;

	static_assert(
		alda::raw::static_size<
			bitfield_binding
		>::value
		==
		fcppt::brigand::ceil_div<
			alda::raw::size_type,
			64u,
			std::numeric_limits<
				alda::raw::data
			>::digits
		>::value,
		""
	);

	bitfield test(
		bitfield::null()
	);

	test[
		42u
	] = true;

	std::stringstream stream{};

	alda::serialization::write<
		bitfield_binding
	>(
		stream,
		test
	);

	CHECK(
		fcppt::catch_::defer(
			alda::serialization::read<
				bitfield_binding
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
