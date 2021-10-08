//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_TYPE_ENUM_HPP_INCLUDED
#define ALDA_TYPE_ENUM_HPP_INCLUDED

#include <alda/type_enum_fwd.hpp>

namespace alda
{

template <typename Enum>
struct type_enum
{
  using type = Enum;
};

}

#endif
