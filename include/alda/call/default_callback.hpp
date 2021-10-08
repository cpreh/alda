//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_CALL_DEFAULT_CALLBACK_HPP_INCLUDED
#define ALDA_CALL_DEFAULT_CALLBACK_HPP_INCLUDED

#include <alda/call/default_function.hpp>
#include <fcppt/function_impl.hpp>

namespace alda::call
{

template <typename TypeEnum, typename Result>
using default_callback = fcppt::function<alda::call::default_function<TypeEnum, Result>>;

}

#endif
