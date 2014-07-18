//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/enum.hpp>
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
	std::uint8_t
> enum_binding;

MAJUTSU_MAKE_ROLE_TAG(
	enum_role
);

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				enum_binding,
				enum_role
			>
		>
	>
> message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_enum
)
{
FCPPT_PP_POP_WARNING

	BOOST_CHECK(
		message(
			enum_role{} =
				test_enum::value0
		).get<
			enum_role
		>()
		== test_enum::value0
	);

	BOOST_CHECK(
		message(
			enum_role{} =
				test_enum::value1
		).get<
			enum_role
		>()
		== test_enum::value1
	);
}
