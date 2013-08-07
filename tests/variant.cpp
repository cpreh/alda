/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <alda/bindings/signed.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/variant/get.hpp>
#include <fcppt/variant/object_impl.hpp>
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
> variant_role;

typedef
fcppt::variant::object<
	types
>
variant_type;

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				variant_role
			>
		>
	>
> message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_variant
)
{
FCPPT_PP_POP_WARNING
	BOOST_CHECK(
		fcppt::variant::get<
			uint_type
		>(
			message(
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
		fcppt::variant::get<
			int_type
		>(
			message(
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
