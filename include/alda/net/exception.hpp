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


#ifndef ALDA_NET_EXCEPTION_HPP_INCLUDED
#define ALDA_NET_EXCEPTION_HPP_INCLUDED

#include <alda/class_symbol.hpp>
#include <alda/exception.hpp>
#include <alda/symbol.hpp>
#include <alda/net/exception_fwd.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace alda
{
namespace net
{

class ALDA_CLASS_SYMBOL exception
:
	public alda::exception
{
public:
	ALDA_SYMBOL
	explicit
	exception(
		fcppt::string const &
	);

	ALDA_SYMBOL
	explicit
	exception(
		fcppt::assert_::information const &
	);
};

}
}

#endif
