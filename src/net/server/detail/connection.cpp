//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/id.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/src/net/server/detail/connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>


alda::net::server::detail::connection::connection(
	alda::net::id const _id,
	alda::net::buffer::max_receive_size const _buffer_receive_size,
	alda::net::buffer::max_send_size const _buffer_send_size,
	boost::asio::io_service &_io_service
)
:
	id_(
		_id
	),
	socket_(
		_io_service
	),
	send_data_(
		_buffer_send_size
	),
	received_data_(
		_buffer_receive_size
	),
	sending_(
		false
	)
{
}

alda::net::server::detail::connection::~connection()
{
}

alda::net::id
alda::net::server::detail::connection::id() const
{
	return
		id_;
}

boost::asio::ip::tcp::socket &
alda::net::server::detail::connection::socket()
{
	return
		socket_;
}

alda::net::buffer::circular_send::object &
alda::net::server::detail::connection::send_data()
{
	return
		send_data_;
}

alda::net::buffer::circular_receive::object &
alda::net::server::detail::connection::received_data()
{
	return
		received_data_;
}

bool &
alda::net::server::detail::connection::sending()
{
	return
		sending_;
}
