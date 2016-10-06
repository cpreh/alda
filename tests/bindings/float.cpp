//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

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
	std::cout
		<< "Comparing "
		<< _val1
		<< " and "
		<< _val2
		<< '\n';


	BOOST_CHECK(
		(_val1 < 0)
		==
		(_val2 < 0)
	);

	typedef
	alda::raw::element_type<
		alda::bindings::float_
	>
	float_type;

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
		0.0001f
	);

	if(
		max < epsilon
	)
		BOOST_CHECK(
			abs1
			<
			epsilon
			&&
			abs2
			<
			epsilon
		);
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
			max > 1.f
		)
			BOOST_CHECK(
				abs_diff
				/
				max
				<
				epsilon
			);
		else
			BOOST_CHECK(
				abs_diff
				<
				epsilon
			);
	}
}

typedef
fcppt::either::object<
	alda::raw::stream::error,
	alda::raw::element_type<
		alda::bindings::float_
	>
>
result_type;

void
fuzzy_equal_either(
	result_type const &_left,
	result_type const &_right
)
{
	BOOST_CHECK(
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
	std::stringstream stream;

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
		result_type{
			_value
		}
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_float_stream
)
{
FCPPT_PP_POP_WARNING

	test_conversion(
		0.f
	);

	test_conversion(
		0.01f
	);

	test_conversion(
		-0.01f
	);

	test_conversion(
		-1.f
	);

	test_conversion(
		1.f
	);

	test_conversion(
		-10000.f
	);

	test_conversion(
		10000.f
	);

	/*
	fuzzy_equal(
		0.1f,
		0.01f
	);

	fuzzy_equal(
		1.f,
		2.f
	);*/
}
