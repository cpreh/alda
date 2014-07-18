//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/bitfield.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/container/bitfield/object.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_bitfield
)
{
FCPPT_PP_POP_WARNING
	typedef
	fcppt::container::bitfield::object<
		unsigned,
		majutsu::integral_size<
			64u
		>
	>
	bitfield;

	typedef
	alda::bindings::bitfield<
		bitfield
	>
	bitfield_binding;

	MAJUTSU_MAKE_ROLE_TAG(
		bitfield_role
	);

	typedef
	alda::message::make_class<
		majutsu::composite<
			boost::mpl::vector1<
				majutsu::role<
					bitfield_binding,
					bitfield_role
				>
			>
		>
	>
	message;

	bitfield test(
		bitfield::null()
	);

	test[
		42u
	] = true;

	BOOST_CHECK(
		message(
			bitfield_role{} =
				test
		).get<
			bitfield_role
		>()
		==
		test
	);
}
