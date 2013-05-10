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


#ifndef ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/endianness/convert.hpp>
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct unsigned_
:
majutsu::fundamental<
	Type
>
{
	static_assert(
		std::is_unsigned<
			Type
		>::value,
		"alda::bindings::unsigned_ only works on unsigned types"
	);
};

FCPPT_PP_POP_WARNING

template<
	typename Type
>
void
place(
	alda::bindings::unsigned_<
		Type
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		majutsu::fundamental<
			Type
		>
	>(
		fcppt::endianness::convert(
			_type,
			alda::endianness()
		),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	alda::bindings::unsigned_<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::endianness::convert(
			majutsu::make<
				majutsu::fundamental<
					Type
				>
			>(
				_beg
			),
			alda::endianness()
		);
}

}
}

namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct static_size<
	alda::bindings::unsigned_<
		Type
	>
>
:
majutsu::static_size<
	majutsu::fundamental<
		Type
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
