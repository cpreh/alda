//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/duration.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/record_variadic.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/endianness/format.hpp>
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
		std::uint32_t,
		fcppt::endianness::format::little
	>,
	std::milli
>
duration;

MAJUTSU_MAKE_ROLE_TAG(
	duration_role
);

typedef
alda::raw::record_variadic<
	majutsu::role<
		duration,
		duration_role
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
	alda::raw::element_type<
		duration
	>
	duration_type;

	BOOST_CHECK(
		majutsu::get<
			duration_role
		>(
			message{
				duration_role{} =
					duration_type(
						10u
					)
			}
		)
		==
		duration_type(
			10u
		)
	);
}
