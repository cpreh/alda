//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/float.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/stream/memory.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace
{

constexpr std::endian const endianness{std::endian::little};

using float_type = alda::raw::element_type<alda::bindings::float_>;

using fixed_int = alda::bindings::float_::fixed_int;

using adapted = alda::bindings::unsigned_<fixed_int, endianness>;

fixed_int const sign_bit(0x1U);

constexpr float_type const exp(fcppt::cast::int_to_float<float_type>(1UL << 16U));

fixed_int make_fixed(float_type const _val)
{
  return static_cast<fixed_int>(std::log(_val + fcppt::literal<float_type>(1)) * exp);
}

float_type unmake_fixed(fixed_int const _val)
{
  return std::exp(fcppt::cast::int_to_float<float_type>(_val) / exp) -
         fcppt::literal<float_type>(1);
}

fixed_int serialize(float_type const _val)
{
  return _val < 0 ? make_fixed(-_val) | sign_bit : make_fixed(_val) & ~sign_bit;
}

float_type deserialize(fixed_int _val)
{
  bool const is_signed((_val & sign_bit) != fcppt::literal<fixed_int>(0));

  _val &= ~sign_bit;

  return is_signed ? unmake_fixed(_val) * fcppt::literal<float_type>(-1) : unmake_fixed(_val);
}

}

void alda::bindings::place(
    alda::raw::dispatch_type<alda::bindings::float_>,
    alda::raw::element_type<alda::bindings::float_> const &_val,
    alda::raw::pointer const _mem)
{
  alda::raw::place<adapted>(serialize(_val), _mem);
}

alda::raw::element_type<alda::bindings::float_>
alda::bindings::make_float(alda::raw::const_pointer _beg)
{
  return deserialize(alda::raw::make_generic<alda::raw::stream::memory, adapted>(_beg));
}
