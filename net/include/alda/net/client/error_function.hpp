//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_CLIENT_ERROR_FUNCTION_HPP_INCLUDED
#define ALDA_NET_CLIENT_ERROR_FUNCTION_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace client
{

typedef
void
error_function(
	fcppt::string const &,
	boost::system::error_code
);

}
}
}

#endif
