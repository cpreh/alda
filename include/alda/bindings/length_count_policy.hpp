//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_LENGTH_COUNT_POLICY_HPP_INCLUDED
#define ALDA_BINDINGS_LENGTH_COUNT_POLICY_HPP_INCLUDED

#include <alda/bindings/length_count_policy_fwd.hpp> // IWYU pragma: keep

namespace alda::bindings
{

struct length_count_policy
{
  template <typename Value>
  inline static decltype(auto) place(Value const &_value)
  {
    return _value.size();
  }

  template <typename Size>
  inline static Size make(Size const _size)
  {
    return _size;
  }
};

}

#endif
