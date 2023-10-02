//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_ENUM_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_HPP_INCLUDED

#include <alda/bindings/enum_decl.hpp> // IWYU pragma: export
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/fail.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/cast/promote_int.hpp>
#include <fcppt/enum/from_int.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::bindings
{

template <typename Enum, typename Adapted>
inline void place(
    alda::raw::dispatch_type<alda::bindings::enum_<Enum, Adapted>>,
    alda::raw::element_type<alda::bindings::enum_<Enum, Adapted>> const &_enum,
    alda::raw::pointer const _mem)
{
  alda::raw::place<Adapted>(
      fcppt::cast::enum_to_int<alda::raw::element_type<Adapted>>(_enum), _mem);
}

template <typename Stream, typename Enum, typename Adapted>
inline alda::raw::stream::result<Stream, alda::bindings::enum_<Enum, Adapted>> make_generic(
    alda::raw::dispatch_type<alda::bindings::enum_<Enum, Adapted>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  return alda::raw::stream::bind<Stream>(
      alda::raw::make_generic<Stream, Adapted>(_stream),
      [](alda::raw::element_type<Adapted> const _element)
      {
        return fcppt::optional::maybe(
            fcppt::enum_::from_int<Enum>(_element),
            [_element]
            {
              return alda::raw::stream::fail<Stream, alda::bindings::enum_<Enum, Adapted>>(
                  FCPPT_TEXT("Invalid value ") +
                  fcppt::output_to_fcppt_string(fcppt::cast::promote_int(_element)));
            },
            [](Enum const _value) { return alda::raw::stream::return_<Stream>(_value); });
      });
}

}

namespace alda::raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Enum, typename Adapted>
struct static_size_impl<alda::bindings::enum_<Enum, Adapted>> : alda::raw::static_size_impl<Adapted>
{
};

FCPPT_PP_POP_WARNING

}

#endif
