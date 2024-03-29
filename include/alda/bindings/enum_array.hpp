//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_ENUM_ARRAY_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_ARRAY_HPP_INCLUDED

#include <alda/bindings/array.hpp>
#include <alda/bindings/enum_array_decl.hpp> // IWYU pragma: export
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
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace alda::bindings
{

template <typename Type, typename Adapted>
inline void place(
    alda::raw::dispatch_type<alda::bindings::enum_array<Type, Adapted>>,
    alda::raw::element_type<alda::bindings::enum_array<Type, Adapted>> const &_value,
    alda::raw::pointer const _mem)
{
  alda::raw::place<alda::bindings::array<typename Type::internal, Adapted>>(_value.impl(), _mem);
}

template <typename Stream, typename Type, typename Adapted>
alda::raw::stream::result<Stream, alda::bindings::enum_array<Type, Adapted>> make_generic(
    alda::raw::dispatch_type<alda::bindings::enum_array<Type, Adapted>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  using array_type = alda::bindings::array<typename Type::internal, Adapted>;

  return alda::raw::stream::bind<Stream>(
      alda::raw::make_generic<Stream, array_type>(_stream),
      [](alda::raw::element_type<array_type> &&_inner)
      {
        return alda::raw::stream::return_<Stream>(
            Type{typename Type::from_internal{}, std::move(_inner)});
      });
}

}

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Type, typename Adapted>
struct static_size_impl<alda::bindings::enum_array<Type, Adapted>>
    : alda::raw::static_size_impl<alda::bindings::array<typename Type::internal, Adapted>>
{
};

FCPPT_PP_POP_WARNING

}

#endif
