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


#ifndef ALDA_BINDINGS_ENUM_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_HPP_INCLUDED

#include <alda/bindings/unsigned.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/cast_to_enum.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Enum,
	typename Underlying
>
struct enum_
{
	typedef Enum type;

	static_assert(
		std::is_enum<
			Enum
		>::value,
		"Enum ist not an enumeration type"
	);
};

template<
	typename Enum,
	typename Underlying
>
void
place(
	alda::bindings::enum_<
		Enum,
		Underlying
	> const *,
	Enum const &_enum,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		alda::bindings::unsigned_<
			Underlying
		>
	>(
		static_cast<
			Underlying
		>(
			_enum
		),
		_mem
	);
}

template<
	typename Enum,
	typename Underlying
>
Enum
make(
	alda::bindings::enum_<
		Enum,
		Underlying
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::cast_to_enum<
			Enum
		>(
			majutsu::make<
				alda::bindings::unsigned_<
					Underlying
				>
			>(
				_beg
			)
		);
}

}
}

namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Enum,
	typename Underlying
>
struct static_size<
	alda::bindings::enum_<
		Enum,
		Underlying
	>
>
:
majutsu::static_size<
	alda::bindings::unsigned_<
		Underlying
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
