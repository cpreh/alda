//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_FLOAT_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_FLOAT_DECL_HPP_INCLUDED

#include <alda/bindings/float_fwd.hpp>
#include <alda/bindings/float_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace alda::bindings
{

struct float_
{
  using element_type = alda::bindings::float_type;

  using fixed_int = std::uint32_t;
};

}

#endif
