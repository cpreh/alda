#include <alda/bindings/fundamental.hpp>
#include <alda/raw/record_variadic.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	raw_record
)
{
FCPPT_PP_POP_WARNING

	typedef
	alda::bindings::fundamental<
		int
	>
	int_;

	typedef
	alda::bindings::fundamental<
		bool
	>
	bool_;

	MAJUTSU_MAKE_ROLE_TAG(
		int_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		bool_role
	);

	typedef
	alda::raw::record_variadic<
		majutsu::role<
			int_,
			int_role
		>,
		majutsu::role<
			bool_,
			bool_role
		>
	>
	my_memory;

	my_memory const test(
		int_role{} = 4,
		bool_role{} = true
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			int_role
		>(
			test
		),
		4
	);

	BOOST_CHECK(
		majutsu::get<
			bool_role
		>(
			test
		)
	);

	my_memory const test2(
		test
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			int_role
		>(
			test2
		),
		4
	);
}
