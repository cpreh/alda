#include <alda/bindings/fundamental.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	raw_nested
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

	FCPPT_RECORD_MAKE_LABEL(
		int_role
	);

	FCPPT_RECORD_MAKE_LABEL(
		record_role
	);

	FCPPT_RECORD_MAKE_LABEL(
		bool_role
	);

	typedef
	alda::raw::record_variadic<
		fcppt::record::element<
			bool_role,
			bool_
		>,
		fcppt::record::element<
			int_role,
			int_
		>
	>
	inner_record;

	typedef
	alda::raw::record_variadic<
		fcppt::record::element<
			int_role,
			int_
		>,
		fcppt::record::element<
			record_role,
			inner_record
		>
	>
	test_record;

	test_record const test{
		int_role{} = 42,
		record_role{} =
			inner_record{
				bool_role{} = false,
				int_role{} = 500
			}
	};

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			int_role
		>(
			test
		),
		42
	);

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			bool_role
		>(
			alda::raw::get<
				record_role
			>(
				test
			)
		),
		false
	);

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			int_role
		>(
			alda::raw::get<
				record_role
			>(
				test
			)
		),
		500
	);
}
