//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_RECORD_VARIADIC_FWD_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_VARIADIC_FWD_HPP_INCLUDED

#include <alda/bindings/record_fwd.hpp> // IWYU pragma: keep
#include <fcppt/mpl/list/object.hpp>

namespace alda::bindings
{

template <typename... Types>
using record_variadic = alda::bindings::record<fcppt::mpl::list::object<Types...>>;

}

#endif
