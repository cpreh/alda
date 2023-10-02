//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_FLOAT_HPP_INCLUDED
#define ALDA_BINDINGS_FLOAT_HPP_INCLUDED

#include <alda/bindings/float_decl.hpp> // IWYU pragma: export
#include <alda/bindings/float_type.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/detail/symbol.hpp>
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
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

ALDA_DETAIL_SYMBOL
void place(
    alda::raw::dispatch_type<alda::bindings::float_>,
    alda::raw::element_type<alda::bindings::float_> const &,
    alda::raw::pointer);

ALDA_DETAIL_SYMBOL
alda::raw::element_type<alda::bindings::float_> make_float(alda::raw::const_pointer);

template <typename Stream>
alda::raw::stream::result<Stream, alda::bindings::float_> make_generic(
    alda::raw::dispatch_type<alda::bindings::float_>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  return alda::raw::stream::bind<Stream>(
      alda::raw::
          make_generic<Stream, alda::bindings::fundamental<alda::bindings::float_::fixed_int>>(
              _stream),
      [](alda::bindings::float_::fixed_int const _value)
      {
        return alda::raw::stream::return_<Stream>(alda::bindings::make_float(
            fcppt::cast::to_char_ptr<alda::raw::const_pointer>(&_value)));
      });
}

}

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <>
struct static_size_impl<alda::bindings::float_>
    : alda::raw::static_size_impl<alda::bindings::fundamental<alda::bindings::float_::fixed_int>>
{
};

FCPPT_PP_POP_WARNING

}

#endif
