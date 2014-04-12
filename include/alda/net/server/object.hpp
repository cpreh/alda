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


#ifndef ALDA_NET_SERVER_OBJECT_HPP_INCLUDED
#define ALDA_NET_SERVER_OBJECT_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/id.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/optional_ref_fwd.hpp>
#include <alda/net/server/connect_callback.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <alda/net/server/object_fwd.hpp>
#include <alda/net/server/detail/object_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	ALDA_DETAIL_SYMBOL
	explicit
	object(
		alda::net::parameters const &
	);

	ALDA_DETAIL_SYMBOL
	~object();

	ALDA_DETAIL_SYMBOL
	void
	listen(
		alda::net::port
	);

	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_send::optional_ref const
	send_buffer(
		alda::net::id
	);

	ALDA_DETAIL_SYMBOL
	alda::net::server::connection_id_container const
	connections() const;

	ALDA_DETAIL_SYMBOL
	void
	queue_send(
		alda::net::id
	);

	ALDA_DETAIL_SYMBOL
	void
	disconnect(
		alda::net::id
	);

	ALDA_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_connect(
		alda::net::server::connect_callback const &
	);

	ALDA_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_disconnect(
		alda::net::server::disconnect_callback const &
	);

	ALDA_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_data(
		alda::net::server::data_callback const &
	);
private:
	std::unique_ptr<
		alda::net::server::detail::object_impl
	> const impl_;
};

}
}
}

#endif
