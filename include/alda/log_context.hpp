//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_LOG_CONTEXT_HPP_INCLUDED
#define ALDA_LOG_CONTEXT_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace alda
{

ALDA_DETAIL_SYMBOL
fcppt::log::context &
log_context();

}

#endif
