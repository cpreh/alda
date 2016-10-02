#include <alda/type_enum.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/record.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
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
	message_record
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
		bool_role
	);

	enum class message_type
	{
		message1,
		fcppt_maximum = message1
	};

	typedef
	alda::type_enum<
		message_type
	>
	type_enum;

	typedef
	alda::message::record<
		alda::message::make_id<
			type_enum,
			message_type::message1
		>,
		boost::mpl::vector2<
			fcppt::record::element<
				int_role,
				int_
			>,
			fcppt::record::element<
				bool_role,
				bool_
			>
		>
	>
	my_memory;

	my_memory const test(
		int_role{} = 4,
		bool_role{} = true
	);


	BOOST_CHECK_EQUAL(
		test.get<
			int_role
		>(),
		4
	);

	BOOST_CHECK(
		test.get<
			bool_role
		>()
	);

	my_memory const test2(
		test
	);

	BOOST_CHECK_EQUAL(
		test2.get<
			int_role
		>(),
		4
	);
}
