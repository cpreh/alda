//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/signed.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/get_exn.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
uint_type;

typedef
std::int16_t
int_type;

typedef
boost::mpl::vector2<
	uint_type,
	int_type
>
types;

typedef
boost::mpl::vector2<
	alda::bindings::unsigned_<
		uint_type
	>,
	alda::bindings::signed_<
		int_type
	>
>
adapted_types;

typedef
alda::bindings::variant<
	types,
	adapted_types
>
variant_binding;

typedef
fcppt::variant::object<
	types
>
variant_type;

MAJUTSU_MAKE_ROLE_TAG(
	variant_role
);

typedef
alda::message::make_class<
	boost::mpl::vector1<
		majutsu::role<
			variant_binding,
			variant_role
		>
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_variant
)
{
FCPPT_PP_POP_WARNING
	BOOST_CHECK(
		fcppt::variant::get_exn<
			uint_type
		>(
			message(
				variant_role{} =
					variant_type(
						static_cast<
							uint_type
						>(
							42u
						)
					)
			).get<
				variant_role
			>()
		)
		==
		static_cast<
			uint_type
		>(
			42u
		)
	);

	BOOST_CHECK(
		fcppt::variant::get_exn<
			int_type
		>(
			message(
				variant_role{} =
					variant_type(
						static_cast<
							int_type
						>(
							13
						)
					)
			).get<
				variant_role
			>()
		)
		==
		static_cast<
			int_type
		>(
			13
		)
	);
}
