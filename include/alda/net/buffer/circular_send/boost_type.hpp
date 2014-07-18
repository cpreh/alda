//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_BOOST_TYPE_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_BOOST_TYPE_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

typedef boost::circular_buffer<
	alda::net::value_type
> boost_type;

}
}
}
}

#endif
