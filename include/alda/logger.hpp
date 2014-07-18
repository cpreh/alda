//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_LOGGER_HPP_INCLUDED
#define ALDA_LOGGER_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace alda
{

ALDA_DETAIL_SYMBOL
fcppt::log::object &
logger();

}

#endif
