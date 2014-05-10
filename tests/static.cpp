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


#include <alda/bindings/static.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
fcppt::math::vector::static_<
	unsigned,
	2
>
int_vec2;

typedef
alda::bindings::static_<
	int_vec2,
	alda::bindings::unsigned_<
		int_vec2::value_type
	>
>
vector_binding;

MAJUTSU_MAKE_ROLE_TAG(
	vector_role
);

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				vector_binding,
				vector_role
			>
		>
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_static
)
{
FCPPT_PP_POP_WARNING

	int_vec2 const test(
		2u,
		5u
	);

	BOOST_CHECK(
		message(
			vector_role{} =
				test
		).get<
			vector_role
		>()
		==
		test
	);
}
