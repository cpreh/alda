//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/impl/net/server/detail/connection.hpp>
#include <alda/net/id.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <alda/net/buffer/circular_send/streambuf.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>

alda::net::server::detail::connection::connection(
    alda::net::id const _id,
    alda::net::buffer::max_receive_size const _buffer_receive_size,
    alda::net::buffer::max_send_size const _buffer_send_size,
    boost::asio::io_context &_io_context)
    : id_(_id),
      // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
      socket_{_io_context},
      send_data_(_buffer_send_size),
      received_data_(_buffer_receive_size),
      sending_(false)
{
}

alda::net::server::detail::connection::~connection() = default;

alda::net::id alda::net::server::detail::connection::id() const { return id_; }

boost::asio::ip::tcp::socket &alda::net::server::detail::connection::socket() { return socket_; }

alda::net::buffer::circular_send::streambuf &alda::net::server::detail::connection::send_data()
{
  return send_data_;
}

alda::net::buffer::circular_receive::streambuf &
alda::net::server::detail::connection::received_data()
{
  return received_data_;
}

bool &alda::net::server::detail::connection::sending() { return sending_; }
