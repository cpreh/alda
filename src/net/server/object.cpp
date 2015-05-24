//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/id.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_send/optional_ref.hpp>
#include <alda/net/server/connect_callback.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <alda/net/server/object.hpp>
#include <alda/src/net/server/detail/object_impl.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/signal/auto_connection.hpp>


alda::net::server::object::object(
	alda::net::parameters const &_parameters
)
:
	impl_(
		fcppt::make_unique_ptr_fcppt<
			alda::net::server::detail::object_impl
		>(
			_parameters
		)
	)
{
}

alda::net::server::object::~object()
{
}

void
alda::net::server::object::listen(
	alda::net::port const _port
)
{
	return
		impl_->listen(
			_port
		);
}

alda::net::buffer::circular_send::optional_ref const
alda::net::server::object::send_buffer(
	alda::net::id const _id
)
{
	return
		impl_->send_buffer(
			_id
		);
}

alda::net::server::connection_id_container
alda::net::server::object::connections() const
{
	return
		impl_->connections();
}

void
alda::net::server::object::queue_send(
	alda::net::id const _id
)
{
	return
		impl_->queue_send(
			_id
		);
}

void
alda::net::server::object::disconnect(
	alda::net::id const _id
)
{
	impl_->disconnect(
		_id
	);
}

fcppt::signal::auto_connection
alda::net::server::object::register_connect(
	alda::net::server::connect_callback const &_callback
)
{
	return
		impl_->register_connect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_disconnect(
	alda::net::server::disconnect_callback const &_callback
)
{
	return
		impl_->register_disconnect(
			_callback
		);
}

fcppt::signal::auto_connection
alda::net::server::object::register_data(
	alda::net::server::data_callback const &_callback
)
{
	return
		impl_->register_data(
			_callback
		);
}
