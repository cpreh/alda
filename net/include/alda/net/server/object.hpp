//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_SERVER_OBJECT_HPP_INCLUDED
#define ALDA_NET_SERVER_OBJECT_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/port_fwd.hpp>
#include <alda/net/buffer/circular_send/optional_streambuf_ref_fwd.hpp>
#include <alda/net/detail/symbol.hpp>
#include <alda/net/server/connect_callback.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <alda/net/server/object_fwd.hpp>
#include <alda/net/server/detail/object_impl_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>

namespace alda::net::server
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
  void listen(alda::net::port);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL alda::net::buffer::circular_send::optional_streambuf_ref
      send_buffer(alda::net::id);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL alda::net::server::connection_id_container
  connections() const;

  ALDA_NET_DETAIL_SYMBOL
  void queue_send(alda::net::id);

  ALDA_NET_DETAIL_SYMBOL
  void disconnect(alda::net::id);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_connect(alda::net::server::connect_callback &&);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_disconnect(alda::net::server::disconnect_callback &&);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL fcppt::signal::auto_connection
  register_data(alda::net::server::data_callback &&);

private:
  fcppt::unique_ptr<alda::net::server::detail::object_impl> const impl_;
};

}

#endif
