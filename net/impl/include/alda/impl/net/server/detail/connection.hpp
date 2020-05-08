//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_IMPL_NET_SERVER_DETAIL_CONNECTION_HPP_INCLUDED
#define ALDA_IMPL_NET_SERVER_DETAIL_CONNECTION_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <alda/net/buffer/circular_send/streambuf.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

class connection
{
	FCPPT_NONMOVABLE(
		connection
	);
public:
	connection(
		alda::net::id,
		alda::net::buffer::max_receive_size,
		alda::net::buffer::max_send_size,
		boost::asio::io_service & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	~connection();

	[[nodiscard]]
	alda::net::id
	id() const;

	[[nodiscard]]
	boost::asio::ip::tcp::socket &
	socket();

	[[nodiscard]]
	alda::net::buffer::circular_send::streambuf &
	send_data();

	[[nodiscard]]
	alda::net::buffer::circular_receive::streambuf &
	received_data();

	[[nodiscard]]
	bool &
	sending();
private:
	alda::net::id const id_;

	boost::asio::ip::tcp::socket socket_;

	alda::net::buffer::circular_send::streambuf send_data_;

	alda::net::buffer::circular_receive::streambuf received_data_;

	bool sending_;
};

}
}
}
}

#endif
