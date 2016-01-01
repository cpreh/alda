//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SRC_NET_CLIENT_DETAIL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_SRC_NET_CLIENT_DETAIL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/connect_function.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/data_function.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/net/client/error_function.hpp>
#include <alda/net/client/detail/object_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace client
{
namespace detail
{

class object_impl
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	explicit
	object_impl(
		alda::net::parameters const &
	);

	~object_impl();

	void
	connect(
		alda::net::host const &,
		alda::net::port
	);

	void
	disconnect();

	alda::net::buffer::circular_send::object &
	send_buffer();

	void
	queue_send();

	fcppt::signal::auto_connection
	register_connect(
		alda::net::client::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_error(
		alda::net::client::error_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		alda::net::client::data_callback const &
	);
private:
	boost::asio::io_service &io_service_;

	boost::asio::ip::tcp::socket socket_;

	boost::asio::ip::tcp::resolver resolver_;

	typedef
	fcppt::unique_ptr<
		boost::asio::ip::tcp::resolver::query
	>
	query_unique_ptr;

	typedef
	fcppt::optional::object<
		query_unique_ptr
	>
	optional_query_unique_ptr;

	optional_query_unique_ptr query_;

	alda::net::buffer::circular_receive::object receive_buffer_;

	alda::net::buffer::circular_send::object send_buffer_;

	fcppt::signal::object<
		alda::net::client::connect_function
	> connect_signal_;

	fcppt::signal::object<
		alda::net::client::error_function
	> error_signal_;

	fcppt::signal::object<
		alda::net::client::data_function
	> data_signal_;

	bool sending_;

	void
	handle_error(
		fcppt::string const &,
		boost::system::error_code const &
	);

	void
	read_handler(
		boost::system::error_code const &,
		std::size_t
	);

	void
	write_handler(
		boost::system::error_code const &,
		std::size_t
	);

	void
	resolve_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator
	);

	void
	connect_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator
	);

	void
	send_data();

	void
	receive_data();

	void
	clear();
};

}
}
}
}

#endif
