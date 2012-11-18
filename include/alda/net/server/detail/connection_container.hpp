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


#ifndef ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED
#define ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/server/detail/connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

typedef boost::ptr_map<
	alda::net::id,
	alda::net::server::detail::connection
> connection_container;

}
}
}
}

#endif
