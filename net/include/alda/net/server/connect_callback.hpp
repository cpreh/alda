//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_SERVER_CONNECT_CALLBACK_HPP_INCLUDED
#define ALDA_NET_SERVER_CONNECT_CALLBACK_HPP_INCLUDED

#include <alda/net/server/connect_function.hpp>
#include <fcppt/function_impl.hpp>


namespace alda
{
namespace net
{
namespace server
{

using
connect_callback
=
fcppt::function<
	alda::net::server::connect_function
>;

}
}
}

#endif
