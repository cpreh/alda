//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/log_location.hpp>
#include <alda/net/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>

fcppt::log::location alda::net::log_location()
{
  return alda::log_location() / fcppt::log::name{FCPPT_TEXT("net")};
}
