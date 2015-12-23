//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/record.hpp>
#include <alda/message/make_class.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/endianness/format.hpp>
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

typedef
std::uint16_t
int_type;

typedef
alda::bindings::fundamental<
	int_type,
	fcppt::endianness::format::little
>
int_alda_type;

MAJUTSU_MAKE_ROLE_TAG(
	int_role
);

typedef
alda::message::make_class<
	boost::mpl::vector1<
		majutsu::role<
			int_alda_type,
			int_role
		>
	>
>
message;

typedef
alda::bindings::record<
	message
>
message_record_type;

MAJUTSU_MAKE_ROLE_TAG(
	record_role
);

typedef
alda::message::make_class<
	boost::mpl::vector1<
		majutsu::role<
			message_record_type,
			record_role
		>
	>
>
message_wrapped;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_record
)
{
FCPPT_PP_POP_WARNING

	message_wrapped const msg(
		record_role{} =
			message{
				int_role{} =
					fcppt::literal<
						int_type
					>(
						42
					)
			}
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			int_role
		>(
			majutsu::get<
				record_role
			>(
				msg
			)
		),
		fcppt::literal<
			int_type
		>(
			42
		)
	);
}
