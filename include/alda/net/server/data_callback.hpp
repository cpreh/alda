//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_SERVER_DATA_CALLBACK_HPP_INCLUDED
#define ALDA_NET_SERVER_DATA_CALLBACK_HPP_INCLUDED

#include <alda/net/server/data_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace server
{

typedef std::function<
	alda::net::server::data_function
> data_callback;

}
}
}

#endif
