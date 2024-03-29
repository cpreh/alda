//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED
#define ALDA_NET_SERVER_DETAIL_CONNECTION_CONTAINER_HPP_INCLUDED

#include <alda/net/id.hpp>
#include <alda/net/server/detail/connection_unique_ptr.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace alda::net::server::detail
{

using connection_container =
    std::map<alda::net::id, alda::net::server::detail::connection_unique_ptr>;

}

#endif
