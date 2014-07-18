//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED
#define ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/server/detail/connection_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

typedef boost::ptr_map<
	alda::net::id,
	alda::net::server::detail::connection
> connection_container;

}
}
}
}

#endif
