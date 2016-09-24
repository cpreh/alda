//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/host.hpp>
#include <alda/net/io_service_wrapper.hpp>
#include <alda/net/log_location.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_send/streambuf.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/src/net/client/detail/object_impl.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/parameters.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/log/format/optional_function.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


alda::net::client::detail::object_impl::object_impl(
	alda::net::parameters const &_parameters
)
:
	log_{
		_parameters.log_context(),
		alda::net::log_location(),
		fcppt::log::parameters{
			fcppt::log::name{
				FCPPT_TEXT("client")
			},
			fcppt::log::format::optional_function()
		}
	},
	io_service_(
		_parameters.io_service_wrapper().get()
	),
	socket_(
		io_service_
	),
	resolver_(
		io_service_
	),
	query_(),
	receive_buffer_(
		_parameters.max_receive_size()
	),
	send_buffer_(
		_parameters.max_send_size()
	),
	connect_signal_(),
	error_signal_(),
	data_signal_(),
	sending_(
		false
	)
{
}

alda::net::client::detail::object_impl::~object_impl()
{
}

void
alda::net::client::detail::object_impl::connect(
	alda::net::host const &_host,
	alda::net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("resolving hostname ")
			<< fcppt::from_std_string(
				_host.get()
			)
			<< FCPPT_TEXT(" on port ")
			<< _port
	);

	query_unique_ptr query(
		fcppt::make_unique_ptr<
			boost::asio::ip::tcp::resolver::query
		>(
			boost::asio::ip::tcp::v4(),
			_host.get(),
			fcppt::insert_to_std_string(
				_port
			)
		)
	);

	// TODO: We should move the query through this function but
	// asio makes it extremely difficult
	resolver_.async_resolve(
		*query,
		std::bind(
			&object_impl::resolve_handler,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	);

	query_ =
		optional_query_unique_ptr(
			std::move(
				query
			)
		);
}

void
alda::net::client::detail::object_impl::disconnect()
{
	this->clear();
}

alda::net::buffer::circular_send::streambuf &
alda::net::client::detail::object_impl::send_buffer()
{
	return
		send_buffer_;
}

void
alda::net::client::detail::object_impl::queue_send()
{
	if(
		!sending_
	)
		this->send_data();
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_connect(
	alda::net::client::connect_callback const &_function
)
{
	return
		connect_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_error(
	alda::net::client::error_callback const &_function
)
{
	return
		error_signal_.connect(
			_function
		);
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_data(
	alda::net::client::data_callback const &_function
)
{
	return
		data_signal_.connect(
			_function
		);
}

void
alda::net::client::detail::object_impl::resolve_handler(
	boost::system::error_code const &_error,
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("resolving address: "),
			_error
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("resolved domain, trying to connect")
	);

	boost::asio::ip::tcp::endpoint const endpoint(
		*_iterator
	);

	socket_.async_connect(
		endpoint,
		std::bind(
			&object_impl::connect_handler,
			this,
			std::placeholders::_1,
			++_iterator
		)
	);
}

void
alda::net::client::detail::object_impl::handle_error(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->clear();

	FCPPT_LOG_ERROR(
		log_,
		fcppt::log::_
			<< _message
			<< FCPPT_TEXT(" (")
			<< fcppt::from_std_string(
				_error.message()
			)
			<< FCPPT_TEXT(')')
	);

	error_signal_(
		_message,
		_error
	);
}

void
alda::net::client::detail::object_impl::read_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("read"),
			_error
		);

		return;
	}

	receive_buffer_.bytes_received(
		_bytes
	);

	FCPPT_LOG_VERBOSE(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("read ")
			<< _bytes
			<< FCPPT_TEXT(" bytes.")
	);

	data_signal_(
		receive_buffer_
	);

	this->receive_data();
}

void
alda::net::client::detail::object_impl::write_handler(
	boost::system::error_code const &_error,
	std::size_t const _bytes
)
{
	if(
		_error
	)
	{
		this->handle_error(
			FCPPT_TEXT("write "),
			_error
		);

		return;
	}

	FCPPT_LOG_VERBOSE(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("wrote ")
			<< _bytes
			<< FCPPT_TEXT(" bytes")
	);

	send_buffer_.bytes_sent(
		_bytes
	);

	if(
		!send_buffer_.empty()
	)
		this->send_data();
	else
		sending_ =
			false;
}

void
alda::net::client::detail::object_impl::connect_handler(
	boost::system::error_code const &_error,
	boost::asio::ip::tcp::resolver::iterator _iterator
)
{
	if(
		_error
	)
	{

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

		// are we at the end of the endpoint list?
		if(
			_iterator == boost::asio::ip::tcp::resolver::iterator()
			||
			_error == boost::asio::error::operation_aborted
		)
		{
			this->handle_error(
				FCPPT_TEXT("exhausted endpoints or connection aborted: "),
				_error
			);

			return;
		}

FCPPT_PP_POP_WARNING

		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_
				<< FCPPT_TEXT("resolving next endpoint")
		);

		boost::asio::ip::tcp::endpoint const endpoint(
			*_iterator
		);

		socket_.async_connect(
			endpoint,
			std::bind(
				&object_impl::connect_handler,
				this,
				std::placeholders::_1,
				++_iterator
			)
		);

		return;
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("connected")
	);

	connect_signal_();

	this->receive_data();
}

void
alda::net::client::detail::object_impl::send_data()
{
	alda::net::buffer::circular_send::streambuf::const_array_range const out_data(
		send_buffer_.send_part()
	);

	sending_ = (out_data.second != 0u);

	if(
		!sending_
	)
		return;

	socket_.async_send(
		boost::asio::buffer(
			out_data.first,
			out_data.second
		),
		std::bind(
			&alda::net::client::detail::object_impl::write_handler,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	);
}

void
alda::net::client::detail::object_impl::receive_data()
{
	FCPPT_ASSERT_PRE(
		!receive_buffer_.next_receive_part().empty()
	);

	socket_.async_receive(
		alda::net::buffer::circular_receive::for_asio(
			receive_buffer_.next_receive_part()
		),
		std::bind(
			&object_impl::read_handler,
			this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	);
}

void
alda::net::client::detail::object_impl::clear()
{
	resolver_.cancel();

	query_ =
		optional_query_unique_ptr();

	socket_.close();

	send_buffer_.clear();

	receive_buffer_.clear();

	sending_ = false;
}
