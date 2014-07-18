//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
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
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

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
	uint_binding
>
dynamic_len_binding;

MAJUTSU_MAKE_ROLE_TAG(
	dynamic_len_role
);

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				dynamic_len_binding,
				dynamic_len_role
			>
		>
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_enum
)
{
FCPPT_PP_POP_WARNING
	uint_vector const vec{
		1,
		2
	};

	BOOST_CHECK(
		message(
			dynamic_len_role{} =
				vec
		).get<
			dynamic_len_role
		>()
		==
		vec
	);
}
