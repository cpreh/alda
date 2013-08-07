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


#ifndef ALDA_SERIALIZATION_LOAD_STATIC_SIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_STATIC_SIZE_HPP_INCLUDED

#include <alda/serialization/istream.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/is_static_size.hpp>
#include <majutsu/make.hpp>
#include <majutsu/raw_data.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <array>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Type
>
struct load<
	Type,
	typename
	boost::enable_if<
		majutsu::is_static_size<
			Type
		>
	>::type
>
{
	static
	typename
	Type::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef std::array<
			majutsu::raw_data,
			majutsu::static_size<
				Type
			>::value
		> buffer_type;

		buffer_type buffer;

		_is.read(
			reinterpret_cast<
				char *
			>(
				buffer.data()
			),
			static_cast<
				std::streamsize
			>(
				buffer.size()
			)
		);

		return
			majutsu::make<
				Type
			>(
				buffer.data()
			);
	}
};

}
}

#endif
