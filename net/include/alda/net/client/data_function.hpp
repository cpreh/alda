//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_CLIENT_DATA_FUNCTION_HPP_INCLUDED
#define ALDA_NET_CLIENT_DATA_FUNCTION_HPP_INCLUDED

#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>


namespace alda::net::client
{

using
data_function
=
void (
	alda::net::buffer::circular_receive::streambuf &
);

}

#endif
