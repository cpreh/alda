//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/exception.hpp>
#include <alda/impl/net/client/detail/object_impl.hpp>
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
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp> // IWYU pragma: keep
#include <cstddef>
#include <utility>
#include <fcppt/config/external_end.hpp>

alda::net::client::detail::object_impl::object_impl(alda::net::parameters const &_parameters)
    : log_{_parameters.log_context(), alda::net::log_location(), fcppt::log::name{FCPPT_TEXT("client")}},
      io_context_{_parameters.io_service_wrapper().get()},
      // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
      socket_{io_context_},
      // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
      resolver_{io_context_},
      receive_buffer_(_parameters.max_receive_size()),
      send_buffer_(_parameters.max_send_size()),
      connect_signal_(),
      error_signal_(),
      data_signal_(),
      sending_(false)
{
}

alda::net::client::detail::object_impl::~object_impl() = default;

void alda::net::client::detail::object_impl::connect(
    alda::net::host const &_host, alda::net::port const _port)
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("resolving hostname ") << fcppt::from_std_string(_host.get())
                      << FCPPT_TEXT(" on port ") << _port)

  this->resolver_.async_resolve(
      _host.get(),
      fcppt::output_to_std_string(_port),
      [this](
          boost::system::error_code const &_error, // NOLINT(misc-include-cleaner)
          boost::asio::ip::tcp::resolver::results_type const &_results)
      { this->resolve_handler(_error, _results); });
}

void alda::net::client::detail::object_impl::disconnect() { this->clear(); }

alda::net::buffer::circular_send::streambuf &alda::net::client::detail::object_impl::send_buffer()
{
  return send_buffer_;
}

void alda::net::client::detail::object_impl::queue_send()
{
  if (!sending_)
  {
    this->send_data();
  }
}

fcppt::signal::auto_connection alda::net::client::detail::object_impl::register_connect(
    alda::net::client::connect_callback &&_function)
{
  return connect_signal_.connect(std::move(_function));
}

fcppt::signal::auto_connection alda::net::client::detail::object_impl::register_error(
    alda::net::client::error_callback &&_function)
{
  return error_signal_.connect(std::move(_function));
}

fcppt::signal::auto_connection
alda::net::client::detail::object_impl::register_data(alda::net::client::data_callback &&_function)
{
  return data_signal_.connect(std::move(_function));
}

void alda::net::client::detail::object_impl::resolve_handler(
    boost::system::error_code const &_error, boost::asio::ip::tcp::resolver::results_type const &_endpoints) // NOLINT(misc-include-cleaner)
{
  if (_error)
  {
    this->handle_error(FCPPT_TEXT("resolving address: "), _error);

    return;
  }

  FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("resolved domain, trying to connect"))

  boost::asio::async_connect(
      this->socket_,
      _endpoints,
      [this](
          boost::system::error_code const &_inner_error,
          boost::asio::ip::tcp::endpoint const &_endpoint) // NOLINT(misc-include-cleaner)
      { this->connect_handler(_inner_error, _endpoint); });
}

void alda::net::client::detail::object_impl::handle_error(
    fcppt::string const &_message, boost::system::error_code const &_error) // NOLINT(misc-include-cleaner)
{
  this->clear();

  FCPPT_LOG_ERROR(
      log_,
      fcppt::log::out << _message << FCPPT_TEXT(" (") << fcppt::from_std_string(_error.message())
                      << FCPPT_TEXT(')'))

  error_signal_(_message, _error);
}

void alda::net::client::detail::object_impl::read_handler(
    boost::system::error_code const &_error, std::size_t const _bytes) // NOLINT(misc-include-cleaner)
{
  if (_error)
  {
    this->handle_error(FCPPT_TEXT("read"), _error);

    return;
  }

  receive_buffer_.bytes_received(_bytes);

  FCPPT_LOG_VERBOSE(log_, fcppt::log::out << FCPPT_TEXT("read ") << _bytes << FCPPT_TEXT(" bytes."))

  data_signal_(receive_buffer_);

  this->receive_data();
}

void alda::net::client::detail::object_impl::write_handler(
    boost::system::error_code const &_error, std::size_t const _bytes) // NOLINT(misc-include-cleaner)
{
  if (_error)
  {
    this->handle_error(FCPPT_TEXT("write "), _error);

    return;
  }

  FCPPT_LOG_VERBOSE(log_, fcppt::log::out << FCPPT_TEXT("wrote ") << _bytes << FCPPT_TEXT(" bytes"))

  send_buffer_.bytes_sent(_bytes);

  if (!send_buffer_.empty())
  {
    this->send_data();
  }
  else
  {
    sending_ = false;
  }
}

void alda::net::client::detail::object_impl::connect_handler(
    boost::system::error_code const &_error, boost::asio::ip::tcp::endpoint const &) // NOLINT(misc-include-cleaner)
{
  if (_error)
  {
    this->handle_error(FCPPT_TEXT("Connection error"), _error);

    return;
  }

  FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("connected"))

  connect_signal_();

  this->receive_data();
}

void alda::net::client::detail::object_impl::send_data()
{
  alda::net::buffer::circular_send::streambuf::const_array_range const out_data(
      send_buffer_.send_part());

  sending_ = (out_data.second != 0U);

  if (!sending_)
  {
    return;
  }

  socket_.async_send(
      boost::asio::buffer(out_data.first, out_data.second),
      [this](boost::system::error_code const &_error, std::size_t const _bytes) // NOLINT(misc-include-cleaner)
      { this->write_handler(_error, _bytes); });
}

void alda::net::client::detail::object_impl::receive_data()
{
  if(receive_buffer_.next_receive_part().empty())
  {
    throw alda::exception{FCPPT_TEXT("receive buffer is empty!")};
  }

  socket_.async_receive(
      alda::net::buffer::circular_receive::for_asio(receive_buffer_.next_receive_part()),
      [this](boost::system::error_code const &_error, std::size_t const _bytes) // NOLINT(misc-include-cleaner)
      { this->read_handler(_error, _bytes); });
}

void alda::net::client::detail::object_impl::clear()
{
  resolver_.cancel();

  socket_.close();

  send_buffer_.clear();

  receive_buffer_.clear();

  sending_ = false;
}
