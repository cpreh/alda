//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_IMPL_NET_SERVER_DETAIL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_IMPL_NET_SERVER_DETAIL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port_fwd.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_send/optional_streambuf_ref_fwd.hpp>
#include <alda/net/server/connect_callback.hpp>
#include <alda/net/server/connect_function.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/data_function.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <alda/net/server/disconnect_function.hpp>
#include <alda/net/server/detail/connection_container.hpp>
#include <alda/net/server/detail/connection_fwd.hpp>
#include <alda/net/server/detail/connection_unique_ptr.hpp>
#include <alda/net/server/detail/object_impl_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp> // IWYU pragma: keep
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace alda::net::server::detail
{

class object_impl
{
  FCPPT_NONMOVABLE(object_impl);

public:
  explicit object_impl(alda::net::parameters const &);

  ~object_impl();

  void listen(alda::net::port);

  [[nodiscard]] alda::net::buffer::circular_send::optional_streambuf_ref send_buffer(alda::net::id);

  [[nodiscard]] alda::net::server::connection_id_container connections() const;

  void queue_send(alda::net::id);

  void disconnect(alda::net::id);

  [[nodiscard]] fcppt::signal::auto_connection
  register_connect(alda::net::server::connect_callback &&);

  [[nodiscard]] fcppt::signal::auto_connection
  register_disconnect(alda::net::server::disconnect_callback &&);

  [[nodiscard]] fcppt::signal::auto_connection register_data(alda::net::server::data_callback &&);

private:
  fcppt::log::object log_;

  boost::asio::io_service &io_service_;

  alda::net::buffer::max_receive_size const buffer_receive_size_;

  alda::net::buffer::max_send_size const buffer_send_size_;

  boost::asio::ip::tcp::acceptor acceptor_;

  alda::net::id::value_type id_counter_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  alda::net::server::detail::connection_container connections_;

  fcppt::signal::object<alda::net::server::connect_function> connect_signal_;

  fcppt::signal::object<alda::net::server::disconnect_function> disconnect_signal_;

  fcppt::signal::object<alda::net::server::data_function> data_signal_;

  void accept();

  void read_handler(
      boost::system::error_code const &, // NOLINT(misc-include-cleaner)
      std::size_t,
      alda::net::server::detail::connection & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  void write_handler(
      boost::system::error_code const &, // NOLINT(misc-include-cleaner)
      std::size_t,
      alda::net::server::detail::connection & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  void accept_handler(
      boost::system::error_code const &, alda::net::server::detail::connection_unique_ptr &&); // NOLINT(misc-include-cleaner)

  void handle_error(
      fcppt::string const &,
      boost::system::error_code const &, // NOLINT(misc-include-cleaner)
      alda::net::server::detail::connection const &);

  void send_data(alda::net::server::detail::connection & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  void receive_data(alda::net::server::detail::connection & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  [[nodiscard]] alda::net::server::detail::connection &connection(alda::net::id);
};

}

#endif
