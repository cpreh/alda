//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED

#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/unsigned_decl.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/endianness/convert.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <fcppt/config/external_end.hpp>

namespace alda::bindings
{

template <typename Type, std::endian Endianness>
inline void place(
    alda::raw::dispatch_type<alda::bindings::unsigned_<Type, Endianness>>,
    alda::raw::element_type<alda::bindings::unsigned_<Type, Endianness>> const &_type,
    alda::raw::pointer const _mem)
{
  alda::raw::place<typename alda::bindings::unsigned_<Type, Endianness>::impl>(
      fcppt::endianness::convert(_type, Endianness), _mem);
}

template <typename Stream, typename Type, std::endian Endianness>
inline alda::raw::stream::result<Stream, alda::bindings::unsigned_<Type, Endianness>> make_generic(
    alda::raw::dispatch_type<alda::bindings::unsigned_<Type, Endianness>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  using impl_type = typename alda::bindings::unsigned_<Type, Endianness>::impl;

  return alda::raw::stream::bind<Stream>(
      alda::raw::make_generic<Stream, impl_type>(_stream),
      [](alda::raw::element_type<impl_type> const _value) {
        return alda::raw::stream::return_<Stream>(fcppt::endianness::convert(_value, Endianness));
      });
}

}

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Type, std::endian Endianness>
struct static_size_impl<alda::bindings::unsigned_<Type, Endianness>>
    : alda::raw::static_size_impl<typename alda::bindings::unsigned_<Type, Endianness>::impl>
{
};

FCPPT_PP_POP_WARNING

}

#endif
