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


#ifndef ALDA_BINDINGS_BOOL_HPP_INCLUDED
#define ALDA_BINDINGS_BOOL_HPP_INCLUDED

#include <alda/bindings/bool_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/static_size.hpp>
#include <majutsu/raw_pointer.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

inline
void
place(
	alda::bindings::bool_ const *,
	alda::bindings::bool_::type const _value,
	majutsu::raw_pointer const _data
)
{
	majutsu::place<
		alda::bindings::bool_::wrapped_type
	>(
		static_cast<
			alda::bindings::bool_::wrapped_type::type
		>(
			_value
		),
		_data
	);
}

inline
alda::bindings::bool_::type
make(
	alda::bindings::bool_ const *,
	majutsu::const_raw_pointer const _data
)
{
	return
		majutsu::make<
			alda::bindings::bool_::wrapped_type
		>(
			_data
		)
		!=
		fcppt::literal<
			alda::bindings::bool_::wrapped_type::type
		>(
			0
		);
}

}
}


namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<>
struct static_size<
	alda::bindings::bool_
>
:
majutsu::static_size<
	alda::bindings::bool_::wrapped_type
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
