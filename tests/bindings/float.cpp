//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_RECORD_MAKE_LABEL(
	float_role
);

typedef
alda::raw::record_variadic<
	fcppt::record::element<
		float_role,
		alda::bindings::float_
	>
>
message;

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

void
test_conversion(
	alda::raw::element_type<
		alda::bindings::float_
	> const _value
)
{
	message const msg(
		float_role{} =
			_value
	);

	fuzzy_equal(
		alda::raw::get<
			float_role
		>(
			msg
		),
		_value
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_float
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
