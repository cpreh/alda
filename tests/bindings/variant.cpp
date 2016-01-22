//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/signed.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant.hpp>
#include <alda/raw/record_variadic.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/get_exn.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
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

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
boost::mpl::vector2<
	alda::bindings::unsigned_<
		uint_type,
		endianness
	>,
	alda::bindings::signed_<
		int_type,
		endianness
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
alda::raw::record_variadic<
	majutsu::role<
		variant_binding,
		variant_role
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

	BOOST_CHECK_EQUAL(
		fcppt::variant::get_exn<
			uint_type
		>(
			majutsu::get<
				variant_role
			>(
				message{
					variant_role{} =
						variant_type(
							fcppt::literal<
								uint_type
							>(
								42u
							)
						)
				}
			)
		),
		fcppt::literal<
			uint_type
		>(
			42u
		)
	);

	BOOST_CHECK_EQUAL(
		fcppt::variant::get_exn<
			int_type
		>(
			majutsu::get<
				variant_role
			>(
				message{
					variant_role{} =
						variant_type(
							fcppt::literal<
								int_type
							>(
								13
							)
						)
				}
			)
		),
		fcppt::literal<
			int_type
		>(
			13
		)
	);
}
