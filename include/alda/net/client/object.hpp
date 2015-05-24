//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_CLIENT_OBJECT_HPP_INCLUDED
#define ALDA_NET_CLIENT_OBJECT_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/net/client/object_fwd.hpp>
#include <alda/net/client/detail/object_impl_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace alda
{
namespace net
{
namespace client
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
	connect(
		alda::net::host const &,
		alda::net::port
	);

	ALDA_DETAIL_SYMBOL
	void
	disconnect();

	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_send::object &
	send_buffer();

	ALDA_DETAIL_SYMBOL
	void
	queue_send();

	ALDA_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_connect(
		alda::net::client::connect_callback const &
	);

	ALDA_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_error(
		alda::net::client::error_callback const &
	);

	ALDA_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_data(
		alda::net::client::data_callback const &
	);
private:
	fcppt::unique_ptr<
		alda::net::client::detail::object_impl
	> const impl_;
};

}
}
}

#endif
