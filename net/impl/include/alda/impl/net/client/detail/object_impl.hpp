//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_IMPL_NET_CLIENT_DETAIL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_IMPL_NET_CLIENT_DETAIL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port_fwd.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <alda/net/buffer/circular_send/streambuf.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/connect_function.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/data_function.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/net/client/error_function.hpp>
#include <alda/net/client/detail/object_impl_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp> // IWYU pragma: keep
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace alda::net::client::detail
{

class object_impl
{
  FCPPT_NONMOVABLE(object_impl);

public:
  explicit object_impl(alda::net::parameters const &);

  ~object_impl();

  void connect(alda::net::host const &, alda::net::port);

  void disconnect();

  alda::net::buffer::circular_send::streambuf &send_buffer();

  void queue_send();

  fcppt::signal::auto_connection register_connect(alda::net::client::connect_callback &&);

  fcppt::signal::auto_connection register_error(alda::net::client::error_callback &&);

  fcppt::signal::auto_connection register_data(alda::net::client::data_callback &&);

private:
  fcppt::log::object log_;

  boost::asio::io_service &io_service_;

  boost::asio::ip::tcp::socket socket_;

  boost::asio::ip::tcp::resolver resolver_;

  using query_unique_ptr = fcppt::unique_ptr<boost::asio::ip::tcp::resolver::query>;

  using optional_query_unique_ptr = fcppt::optional::object<query_unique_ptr>;

  optional_query_unique_ptr query_;

  alda::net::buffer::circular_receive::streambuf receive_buffer_;

  alda::net::buffer::circular_send::streambuf send_buffer_;

  fcppt::signal::object<alda::net::client::connect_function> connect_signal_;

  fcppt::signal::object<alda::net::client::error_function> error_signal_;

  fcppt::signal::object<alda::net::client::data_function> data_signal_;

  bool sending_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  // NOLINTNEXTLINE(misc-include-cleaner)
  void handle_error(fcppt::string const &, boost::system::error_code const &);
  // NOLINTNEXTLINE(misc-include-cleaner)
  void read_handler(boost::system::error_code const &, std::size_t);

  // NOLINTNEXTLINE(misc-include-cleaner)
  void write_handler(boost::system::error_code const &, std::size_t);

  // NOLINTNEXTLINE(misc-include-cleaner)
  void resolve_handler(boost::system::error_code const &, boost::asio::ip::tcp::resolver::iterator);

  // NOLINTNEXTLINE(misc-include-cleaner)
  void connect_handler(boost::system::error_code const &, boost::asio::ip::tcp::resolver::iterator);

  void send_data();

  void receive_data();

  void clear();
};

}

#endif
