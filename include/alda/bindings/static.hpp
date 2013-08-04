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


#ifndef ALDA_BINDINGS_STATIC_HPP_INCLUDED
#define ALDA_BINDINGS_STATIC_HPP_INCLUDED

#include <alda/bindings/static_fwd.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/integral_size.hpp>
#include <majutsu/make.hpp>
#include <majutsu/needed_size.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/multiplies.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct static_
{
	typedef Type type;
};

template<
	typename Type,
	typename Adapted
>
void
place(
	alda::bindings::static_<
		Type,
		Adapted
	> const *,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	for(
		auto const &elem : _value
	)
	{
		majutsu::place<
			Adapted
		>(
			elem,
			_mem
		);

		_mem +=
			majutsu::needed_size<
				Adapted
			>(
				elem
			);
	}
}

template<
	typename Type,
	typename Adapted
>
Type
make(
	alda::bindings::static_<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer _mem
)
{
	Type ret{
		fcppt::no_init()
	};

	for(
		auto &elem : ret
	)
	{
		elem =
			majutsu::make<
				Adapted
			>(
				_mem
			);

		_mem +=
			majutsu::needed_size<
				Adapted
			>(
				elem
			);
	}

	return ret;
}

}
}

namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type,
	typename Adapted
>
struct static_size<
	alda::bindings::static_<
		Type,
		Adapted
	>
>
:
boost::mpl::multiplies<
	typename Type::dim_wrapper,
	majutsu::static_size<
		Adapted
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
