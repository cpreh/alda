//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_FOR_ASIO_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_FOR_ASIO_HPP_INCLUDED

#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
// TODO(philipp): Check why this doesn't work:
#include <boost/asio/buffer.hpp> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

namespace alda::net::buffer::circular_receive
{

boost::asio::mutable_buffer for_asio(alda::net::buffer::circular_receive::part const &);

}

#endif
