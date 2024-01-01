//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_BITFIELD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_BITFIELD_DECL_HPP_INCLUDED

#include <alda/bindings/array_fwd.hpp>
#include <alda/bindings/bitfield_fwd.hpp> // IWYU pragma: keep
#include <alda/bindings/unsigned_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <fcppt/config/external_end.hpp>

namespace alda::bindings
{

template <typename Type, std::endian Endianness>
struct bitfield
{
  using element_type = Type;

  using wrapped = alda::bindings::array<
      typename element_type::array_type,
      alda::bindings::unsigned_<typename element_type::internal_type, Endianness>>;
};

}

#endif
