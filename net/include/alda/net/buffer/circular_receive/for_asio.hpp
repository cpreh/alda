//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_FOR_ASIO_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_FOR_ASIO_HPP_INCLUDED

#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <fcppt/config/external_end.hpp>

namespace alda::net::buffer::circular_receive
{

boost::asio::mutable_buffers_1 for_asio(alda::net::buffer::circular_receive::part const &);

}

#endif
