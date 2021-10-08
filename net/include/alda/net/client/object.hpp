//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_CLIENT_OBJECT_HPP_INCLUDED
#define ALDA_NET_CLIENT_OBJECT_HPP_INCLUDED

#include <alda/net/host.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port_fwd.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <alda/net/client/object_fwd.hpp>
#include <alda/net/client/detail/object_impl_fwd.hpp>
#include <alda/net/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>

namespace alda::net::client
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  ALDA_NET_DETAIL_SYMBOL
  explicit object(alda::net::parameters const &);

  ALDA_NET_DETAIL_SYMBOL
  ~object();

  ALDA_NET_DETAIL_SYMBOL
  void connect(alda::net::host const &, alda::net::port);

  ALDA_NET_DETAIL_SYMBOL
  void disconnect();

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL alda::net::buffer::circular_send::streambuf &send_buffer();

  ALDA_NET_DETAIL_SYMBOL
  void queue_send();

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_connect(alda::net::client::connect_callback &&);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_error(alda::net::client::error_callback &&);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_data(alda::net::client::data_callback &&);

private:
  fcppt::unique_ptr<alda::net::client::detail::object_impl> const impl_;
};

}

#endif
