//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_UNIT_HPP_INCLUDED
#define ALDA_BINDINGS_UNIT_HPP_INCLUDED

#include <alda/bindings/unit_decl.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::bindings
{

inline void place(
    alda::raw::dispatch_type<alda::bindings::unit>,
    alda::raw::element_type<alda::bindings::unit> const &,
    alda::raw::pointer)
{
}

template <typename Stream>
inline alda::raw::stream::result<Stream, alda::bindings::unit> make_generic(
    alda::raw::dispatch_type<alda::bindings::unit>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream>)
{
  return alda::raw::stream::return_<Stream>(fcppt::unit{});
}

}

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <>
struct static_size_impl<alda::bindings::unit> : alda::raw::integral_size<0u>
{
};

FCPPT_PP_POP_WARNING

}

#endif
