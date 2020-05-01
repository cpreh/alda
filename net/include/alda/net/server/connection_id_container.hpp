//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_SERVER_CONNECTION_ID_CONTAINER_HPP_INCLUDED
#define ALDA_NET_SERVER_CONNECTION_ID_CONTAINER_HPP_INCLUDED

#include <alda/net/server/detail/connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/adaptor/map.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{

typedef boost::select_first_range<
	alda::net::server::detail::connection_container
> connection_id_container;

}
}
}

#endif
