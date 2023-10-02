//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_STRONG_TYPEDEF_HPP_INCLUDED
#define ALDA_BINDINGS_STRONG_TYPEDEF_HPP_INCLUDED

#include <alda/bindings/strong_typedef_decl.hpp> // IWYU pragma: export
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
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::bindings
{

template <typename Type, typename Adapted>
inline void place(
    alda::raw::dispatch_type<alda::bindings::strong_typedef<Type, Adapted>>,
    alda::raw::element_type<alda::bindings::strong_typedef<Type, Adapted>> const &_value,
    alda::raw::pointer const _mem)
{
  alda::raw::place<Adapted>(_value.get(), _mem);
}

template <typename Stream, typename Type, typename Adapted>
inline alda::raw::stream::result<Stream, alda::bindings::strong_typedef<Type, Adapted>>
make_generic(
    alda::raw::dispatch_type<alda::bindings::strong_typedef<Type, Adapted>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  return alda::raw::stream::bind<Stream>(
      alda::raw::make_generic<Stream, Adapted>(_stream),
      [](alda::raw::element_type<Adapted> &&_inner)
      { return alda::raw::stream::return_<Stream>(Type{std::move(_inner)}); });
}

}

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Type, typename Adapted>
struct static_size_impl<alda::bindings::strong_typedef<Type, Adapted>>
    : alda::raw::static_size_impl<Adapted>
{
};

FCPPT_PP_POP_WARNING

}

#endif
