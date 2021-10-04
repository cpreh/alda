//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

static_assert(
	alda::raw::static_size<
		alda::bindings::float_
	>::value
	== // NOLINT(misc-redundant-expression)
	alda::raw::static_size<
		alda::bindings::fundamental<
			alda::bindings::float_::fixed_int
		>
	>::value
);

void
fuzzy_equal(
	alda::raw::element_type<
		alda::bindings::float_
	> const _val1,
	alda::raw::element_type<
		alda::bindings::float_
	> const _val2
)
{
	CHECK(
		(_val1 < 0)
		==
		(_val2 < 0)
	);

	using
	float_type
	=
	alda::raw::element_type<
		alda::bindings::float_
	>;

	float_type const abs1(
		std::abs(
			_val1
		)
	);

	float_type const abs2(
		std::abs(
			_val2
		)
	);

	float_type const max(
		std::max(
			abs1,
			abs2
		)
	);

	float_type const epsilon(
		0.0001F
	);

	if(
		max < epsilon
	)
	{
		CHECK(
			abs1
			<
			epsilon
		);

		CHECK(
			abs2
			<
			epsilon
		);
	}
	else
	{
		float_type const abs_diff(
			std::abs(
				_val1
				-
				_val2
			)
		);

		if(
			max > 1.F
		)
		{
			CHECK(
				abs_diff
				/
				max
				<
				epsilon
			);
		}
		else
		{
			CHECK(
				abs_diff
				<
				epsilon
			);
		}
	}
}

using
either_result_type
=
fcppt::either::object<
	alda::raw::stream::error,
	alda::raw::element_type<
		alda::bindings::float_
	>
>;

void
fuzzy_equal_either(
	either_result_type const &_left,
	either_result_type const &_right
)
{
	CHECK(
		fcppt::either::apply(
			[](
				alda::raw::element_type<
					alda::bindings::float_
				> const _inner_left,
				alda::raw::element_type<
					alda::bindings::float_
				> const _inner_right
			)
			{
				fuzzy_equal(
					_inner_left,
					_inner_right
				);

				return
					fcppt::unit{};
			},
			_left,
			_right
		).has_success()
	);
}

void
test_conversion(
	alda::raw::element_type<
		alda::bindings::float_
	> const _value
)
{
	// NOLINTNEXTLINE(fuchsia-default-arguments-calls)
	std::stringstream stream{};

	alda::serialization::write<
		alda::bindings::float_
	>(
		stream,
		_value
	);

	fuzzy_equal_either(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			alda::bindings::float_
		>(
			stream
		),
		either_result_type{
			_value
		}
	);
}

}

FCPPT_CATCH_BEGIN

TEST_CASE(
	"bindings::float",
	"[catch]"
)
{
	test_conversion(
		0.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);

	test_conversion(
		0.01F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);

	test_conversion(
		-0.01F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);

	test_conversion(
		-1.F
	);

	test_conversion(
		1.F
	);

	test_conversion(
		-10000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);

	test_conversion(
		10000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	);

	/*
	fuzzy_equal(
		0.1f,
		0.01f
	);

	fuzzy_equal(
		1.F,
		2.F
	);*/
}

FCPPT_CATCH_END
