//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/net/client/object.hpp>
#include <alda/src/net/client/detail/object_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


alda::net::client::object::object(
	alda::net::parameters const &_parameters
)
:
	impl_(
		fcppt::make_unique_ptr<
			alda::net::client::detail::object_impl
		>(
			_parameters
		)
	)
{
}

alda::net::client::object::~object()
{
}

void
alda::net::client::object::connect(
	alda::net::host const &_host,
	alda::net::port const _port
)
{
	return
		impl_->connect(
			_host,
			_port
		);
}

void
alda::net::client::object::disconnect()
{
	return
		impl_->disconnect();
}

alda::net::buffer::circular_send::streambuf &
alda::net::client::object::send_buffer()
{
	return
		impl_->send_buffer();
}

void
alda::net::client::object::queue_send()
{
	impl_->queue_send();
}

fcppt::signal::auto_connection
alda::net::client::object::register_connect(
	alda::net::client::connect_callback &&_callback
)
{
	return
		impl_->register_connect(
			std::move(
				_callback
			)
		);
}

fcppt::signal::auto_connection
alda::net::client::object::register_error(
	alda::net::client::error_callback &&_callback
)
{
	return
		impl_->register_error(
			std::move(
				_callback
			)
		);
}

fcppt::signal::auto_connection
alda::net::client::object::register_data(
	alda::net::client::data_callback &&_callback
)
{
	return
		impl_->register_data(
			std::move(
				_callback
			)
		);
}
