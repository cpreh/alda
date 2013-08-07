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


#ifndef ALDA_SERIALIZATION_LOAD_OPTIONAL_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_OPTIONAL_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <fcppt/io/read.hpp>


namespace alda
{
namespace serialization
{

template<
	typename T,
	typename A
>
struct load<
	alda::bindings::optional<
		T,
		A
	>
>
{
	static
	typename
	alda::bindings::optional<
		T,
		A
	>::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef
		alda::bindings::optional<
			T,
			A
		> type;

		typedef typename type::bool_type::type bool_type;

		bool_type const is_set(
			*fcppt::io::read<
				bool_type
			>(
				_is,
				alda::endianness()
			)
		);

		typedef
		typename
		type::type
		optional_type;

		return
			is_set
			?
				optional_type(
					alda::serialization::load<
						A
					>::get(
						_is
					)
				)
			:
				optional_type()
			;
	}
};

}
}

#endif
