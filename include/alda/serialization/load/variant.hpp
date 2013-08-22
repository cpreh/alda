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


#ifndef ALDA_SERIALIZATION_LOAD_VARIANT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_VARIANT_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/variant_decl.hpp>
#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/load_variant.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/mpl/invoke_on.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Types,
	typename AdaptedTypes
>
struct load<
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
>
{
	static
	typename
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef
		alda::bindings::variant<
			Types,
			AdaptedTypes
		> type;

		return
			fcppt::mpl::invoke_on<
				Types
			>(
				*fcppt::io::read<
					typename type::index_type::type
				>(
					_is,
					alda::endianness()
				),
				alda::serialization::detail::load_variant<
					Types,
					AdaptedTypes
				>(
					_is
				)
			);
	}
};

}
}

#endif
