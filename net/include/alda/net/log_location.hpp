//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_LOG_LOCATION_HPP_INCLUDED
#define ALDA_NET_LOG_LOCATION_HPP_INCLUDED

#include <alda/net/detail/symbol.hpp>
#include <fcppt/log/location.hpp>

namespace alda::net
{

ALDA_NET_DETAIL_SYMBOL
fcppt::log::location log_location();

}

#endif
