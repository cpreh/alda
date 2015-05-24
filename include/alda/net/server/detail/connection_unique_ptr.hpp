//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_SERVER_DETAIL_CONNECTION_UNIQUE_PTR_HPP_INCLUDED
#define ALDA_NET_SERVER_DETAIL_CONNECTION_UNIQUE_PTR_HPP_INCLUDED

#include <fcppt/unique_ptr_impl.hpp>
#include <alda/net/server/detail/connection_fwd.hpp>


namespace alda
{
namespace net
{
namespace server
{
namespace detail
{

typedef
fcppt::unique_ptr<
	alda::net::server::detail::connection
>
connection_unique_ptr;

}
}
}
}

#endif
