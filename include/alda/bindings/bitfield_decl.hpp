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


#ifndef ALDA_BINDINGS_BITFIELD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_BITFIELD_DECL_HPP_INCLUDED

#include <alda/bindings/array_fwd.hpp>
#include <alda/bindings/bitfield_fwd.hpp>
#include <alda/bindings/unsigned_fwd.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type
>
struct bitfield
{
	typedef
	Type
	type;

	typedef
	alda::bindings::array<
		typename
		type::array_type,
		alda::bindings::unsigned_<
			typename
			type::internal_type
		>
	>
	wrapped;
};

}
}

#endif
