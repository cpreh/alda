//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/impl/net/server/detail/connection.hpp>
#include <alda/impl/net/server/detail/object_impl.hpp>
#include <alda/net/id.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <alda/net/log_location.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_send/optional_streambuf_ref.hpp>
#include <alda/net/buffer/circular_send/streambuf.hpp>
#include <alda/net/server/connect_callback.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <alda/net/server/detail/connection_container.hpp>
#include <alda/net/server/detail/connection_unique_ptr.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/format/optional_function.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


alda::net::server::detail::object_impl::object_impl(
	alda::net::parameters const &_parameters
)
:
	log_{
		_parameters.log_context(),
		alda::net::log_location(),
		fcppt::log::parameters{
			fcppt::log::name{
				FCPPT_TEXT("server")
			},
			fcppt::log::format::optional_function()
		}
	},
	io_service_(
		_parameters.io_service_wrapper().get()
	),
	buffer_receive_size_(
		_parameters.max_receive_size()
	),
	buffer_send_size_(
		_parameters.max_send_size()
	),
	acceptor_(
		io_service_
	),
	id_counter_(
		0u
	),
	connections_(),
	connect_signal_(),
	disconnect_signal_(),
	data_signal_()
{
}

alda::net::server::detail::object_impl::~object_impl()
{
}

void
alda::net::server::detail::object_impl::listen(
	alda::net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("listening on port ")
			<< _port
	)

	boost::asio::ip::tcp::endpoint const endpoint(
		boost::asio::ip::tcp::v4(),
		fcppt::cast::size<
			unsigned short
		>(
			_port.get()
		)
	);

	acceptor_.open(
		endpoint.protocol()
	);

	acceptor_.set_option(
		boost::asio::ip::tcp::acceptor::reuse_address(
			true
		)
	);

	acceptor_.bind(
		endpoint
	);

	acceptor_.listen();

	this->accept();
}

alda::net::buffer::circular_send::optional_streambuf_ref
alda::net::server::detail::object_impl::send_buffer(
	alda::net::id const _id
)
{
	return
		fcppt::optional::bind(
			fcppt::container::find_opt_mapped(
				connections_,
				_id
			),
			[](
				fcppt::reference<
					alda::net::server::detail::connection_container::mapped_type
				> const _connection
			)
			{
				return
					alda::net::buffer::circular_send::optional_streambuf_ref{
						fcppt::make_ref(
							_connection.get()->send_data()
						)
					};
			}
		);
}

alda::net::server::connection_id_container
alda::net::server::detail::object_impl::connections() const
{
	return
		boost::adaptors::keys(
			connections_
		);
}

void
alda::net::server::detail::object_impl::queue_send(
	alda::net::id const _id
)
{
	alda::net::server::detail::connection &con(
		this->connection(
			_id
		)
	);

	if(
		!con.sending()
	)
		this->send_data(
			con
		);
}

void
alda::net::server::detail::object_impl::disconnect(
	alda::net::id const _id
)
{
	this->connection(
		_id
	).socket().shutdown(
		boost::asio::ip::tcp::socket::shutdown_both
	);
}

fcppt::signal::auto_connection
alda::net::server::detail::object_impl::register_connect(
	alda::net::server::connect_callback &&_callback
)
{
	return
		connect_signal_.connect(
			std::move(
				_callback
			)
		);
}

fcppt::signal::auto_connection
alda::net::server::detail::object_impl::register_disconnect(
	alda::net::server::disconnect_callback &&_callback
)
{
	return
		disconnect_signal_.connect(
			std::move(
				_callback
			)
		);
}

fcppt::signal::auto_connection
alda::net::server::detail::object_impl::register_data(
	alda::net::server::data_callback &&_callback
)
{
	return
		data_signal_.connect(
			std::move(
				_callback
			)
		);
}

void
alda::net::server::detail::object_impl::accept()
{
	alda::net::server::detail::connection_unique_ptr con(
		fcppt::make_unique_ptr<
			alda::net::server::detail::connection
		>(
			alda::net::id(
				id_counter_++
			),
			buffer_receive_size_,
			buffer_send_size_,
			io_service_
		)
	);

	boost::asio::ip::tcp::socket &socket(
		con->socket()
	);

	class handler
	{
	public:
		handler(
			object_impl &_object,
			alda::net::server::detail::connection_unique_ptr &&_connection
		)
		:
			object_(
				_object
			),
			connection_(
				std::move(
					_connection
				)
			)
		{
		}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4822)
		// Asio checks for the presence of a copy-constructor but doesn't use it
		handler(
			handler const &
		);
FCPPT_PP_POP_WARNING

		handler(
			handler &&
		) = default;

		handler &
		operator=(
			handler const &
		) = delete;

		void
		operator()(
			boost::system::error_code const &_error
		)
		{
			object_.accept_handler(
				_error,
				std::move(
					connection_
				)
			);
		}
	private:
		object_impl &object_;

		alda::net::server::detail::connection_unique_ptr connection_;
	};

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

	acceptor_.async_accept(
		socket,
		handler(
			*this,
			std::move(
				con
			)
		)
	);

FCPPT_PP_POP_WARNING
}

void
alda::net::server::detail::object_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes,
	alda::net::server::detail::connection &_con
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("server read"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("reading ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	)

	_con.received_data().bytes_received(
		_bytes
	);

	data_signal_(
		_con.id(),
		_con.received_data()
	);

	this->receive_data(
		_con
	);
}

void
alda::net::server::detail::object_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes,
	alda::net::server::detail::connection &_con
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("write"),
			_error,
			_con
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("wrote ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	)

	alda::net::buffer::circular_send::streambuf &sent_data(
		_con.send_data()
	);

	sent_data.bytes_sent(
		_bytes
	);

	if(
		!sent_data.empty()
	)
		this->send_data(
			_con
		);
	else
		_con.sending() = false;
}

void
alda::net::server::detail::object_impl::accept_handler(
	boost::system::error_code const &_error,
	alda::net::server::detail::connection_unique_ptr &&_new_connection
)
{
	if(
		_error
	)
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::out
				<< FCPPT_TEXT("error while accepting")
		)

		this->accept();

		return;
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("accepting a connection, id is ")
			<< _new_connection->id()
	)

	alda::net::id const new_id(
		_new_connection->id()
	);

	std::pair<
		alda::net::server::detail::connection_container::iterator,
		bool
	> const result(
		connections_.emplace(
			new_id,
			std::move(
				_new_connection
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		result.second
	);

	// send signal to handlers
	connect_signal_(
		result.first->second->id()
	);

	this->receive_data(
		*result.first->second
	);

	this->accept();
}

void
alda::net::server::detail::object_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error,
	alda::net::server::detail::connection const &_con
)
{
	fcppt::string const error_msg(
		_message
		+ FCPPT_TEXT(": ")
		+
		fcppt::from_std_string(
			_error.message()
		)
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("disconnected ")
			<< _con.id()
			<< FCPPT_TEXT(" (")
			<< error_msg
			<< FCPPT_TEXT(")")
	)

	alda::net::id const id(
		_con.id()
	);

	FCPPT_ASSERT_ERROR(
		connections_.erase(
			id
		)
	);

	disconnect_signal_(
		id,
		error_msg
	);
}

void
alda::net::server::detail::object_impl::send_data(
	alda::net::server::detail::connection &_con
)
{
	alda::net::buffer::circular_send::streambuf::const_array_range const out_data(
		_con.send_data().send_part()
	);

	_con.sending() = (out_data.second != 0u);

	if(
		!_con.sending()
	)
		return;

	_con.socket().async_send(
		boost::asio::buffer(
			out_data.first,
			out_data.second
		),
		std::bind(
			&object_impl::write_handler,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::ref(
				_con
			)
		)
	);
}

void
alda::net::server::detail::object_impl::receive_data(
	alda::net::server::detail::connection &_con
)
{
	FCPPT_ASSERT_PRE(
		!_con.received_data().next_receive_part().empty()
	);

	// receive some more
	_con.socket().async_receive(
		alda::net::buffer::circular_receive::for_asio(
			_con.received_data().next_receive_part()
		),
		std::bind(
			&alda::net::server::detail::object_impl::read_handler,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::ref(
				_con
			)
		)
	);
}

alda::net::server::detail::connection &
alda::net::server::detail::object_impl::connection(
	alda::net::id const _id
)
{
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::container::find_opt_mapped(
				connections_,
				_id
			)
		).get();
}
