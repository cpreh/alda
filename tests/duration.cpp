#include <alda/bindings/duration.hpp>
#include <alda/bindings/unsigned.hpp>
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
#include <ratio>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
alda::bindings::duration<
	alda::bindings::unsigned_<
		std::uint32_t
	>,
	std::milli
>
duration;

MAJUTSU_MAKE_ROLE_TAG(
	duration_role
);

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				duration,
				duration_role
			>
		>
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_duration
)
{
FCPPT_PP_POP_WARNING

	typedef
	duration::type
	duration_type;

	BOOST_CHECK(
		message(
			duration_role{} =
				duration_type(
					10u
				)
		).get<
			duration_role
		>()
		==
		duration_type(
			10u
		)
	);
}
