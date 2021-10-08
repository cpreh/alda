//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_STRONG_TYPEDEF_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_STRONG_TYPEDEF_DECL_HPP_INCLUDED

#include <alda/bindings/strong_typedef_fwd.hpp>
#include <fcppt/is_strong_typedef.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::bindings
{

template <typename Type, typename Adapted>
struct strong_typedef
{
  static_assert(fcppt::is_strong_typedef<Type>::value, "Type must be an fcppt::strong_typedef");

  using element_type = Type;

  using adapted = Adapted;
};

}

#endif
