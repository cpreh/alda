//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_FUNDAMENTAL_HPP_INCLUDED
#define ALDA_BINDINGS_FUNDAMENTAL_HPP_INCLUDED

#include <alda/bindings/fundamental_decl.hpp> // IWYU pragma: export
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/detail/copy_n.hpp>
#include <alda/raw/stream/read.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return_if.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename T>
struct static_size_impl<alda::bindings::fundamental<T>> : alda::raw::integral_size<sizeof(T)>
{
};

FCPPT_PP_POP_WARNING

}

namespace bindings
{

template <typename Type>
inline void place(
    alda::raw::dispatch_type<alda::bindings::fundamental<Type>>,
    Type const &_value,
    alda::raw::pointer const _memory)
{
  alda::raw::detail::copy_n(
      fcppt::cast::to_char_ptr<alda::raw::const_pointer>(&_value),
      alda::raw::static_size<alda::bindings::fundamental<Type>>::value,
      _memory);
}

template <typename Type, typename Stream>
inline alda::raw::stream::result<Stream, alda::bindings::fundamental<Type>> make_generic(
    alda::raw::dispatch_type<alda::bindings::fundamental<Type>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  Type ret;

  alda::raw::stream::read<Stream>(
      _stream,
      alda::raw::static_size<alda::bindings::fundamental<Type>>::value,
      fcppt::cast::to_char_ptr<alda::raw::pointer>(&ret));

  return alda::raw::stream::return_if<Stream, alda::bindings::fundamental<Type>>(_stream, ret);
}

}
}

#endif
