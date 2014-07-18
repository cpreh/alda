//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_MAX_RECEIVE_SIZE_HPP_INCLUDED
#define ALDA_NET_BUFFER_MAX_RECEIVE_SIZE_HPP_INCLUDED

#include <alda/net/size_type.hpp>
#include <fcppt/strong_typedef.hpp>


namespace alda
{
namespace net
{
namespace buffer
{

FCPPT_MAKE_STRONG_TYPEDEF(
	alda::net::size_type,
	max_receive_size
);

}
}
}

#endif
