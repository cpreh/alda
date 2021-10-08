//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_DYNAMIC_LEN_FWD_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_FWD_HPP_INCLUDED

#include <alda/bindings/length_count_policy_fwd.hpp>

namespace alda::bindings
{

template <
    typename Type,
    typename Adapted,
    typename Length,
    typename LengthPolicy = alda::bindings::length_count_policy>
struct dynamic_len;

}

#endif
