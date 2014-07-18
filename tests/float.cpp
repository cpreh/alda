//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
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

MAJUTSU_MAKE_ROLE_TAG(
	float_role
);

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				alda::bindings::float_,
				float_role
			>
		>
	>
> message;

void
fuzzy_equal(
	alda::bindings::float_::type const _val1,
	alda::bindings::float_::type const _val2
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

	alda::bindings::float_::type const abs1(
		std::abs(
			_val1
		)
	);

	alda::bindings::float_::type const abs2(
		std::abs(
			_val2
		)
	);

	alda::bindings::float_::type const max(
		std::max(
			abs1,
			abs2
		)
	);

	alda::bindings::float_::type const epsilon(
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
		alda::bindings::float_::type const abs_diff(
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
	alda::bindings::float_::type const _value
)
{
	message const msg(
		float_role{} =
			_value
	);

	fuzzy_equal(
		msg.get<
			float_role
		>(),
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
