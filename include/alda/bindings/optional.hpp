//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED
#define ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED

#include <alda/bindings/bool.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/needed_size_static.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/const.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace alda::bindings
{

template <typename Type, typename Adapted>
void place(
    alda::raw::dispatch_type<alda::bindings::optional<Type, Adapted>>,
    alda::raw::element_type<alda::bindings::optional<Type, Adapted>> const &_opt_value,
    alda::raw::pointer _mem)
{
  using binding = alda::bindings::optional<Type, Adapted>;

  using bool_type = typename binding::bool_type;

  _mem = alda::raw::place_and_update<bool_type>(_opt_value.has_value(), _mem);

  fcppt::optional::maybe_void(
      _opt_value, [_mem](Type const &_value) { alda::raw::place<Adapted>(_value, _mem); });
}

template <typename Stream, typename Type, typename Adapted>
alda::raw::stream::result<Stream, alda::bindings::optional<Type, Adapted>> make_generic(
    alda::raw::dispatch_type<alda::bindings::optional<Type, Adapted>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  using bool_type = typename alda::bindings::optional<Type, Adapted>::bool_type;

  return alda::raw::stream::bind<Stream>(
      alda::raw::make_generic<Stream, bool_type>(_stream),
      [&_stream](alda::raw::element_type<bool_type> const _has_value)
      {
        return _has_value ? alda::raw::stream::bind<Stream>(
                                alda::raw::make_generic<Stream, Adapted>(_stream),
                                [](alda::raw::element_type<Adapted> &&_inner) {
                                  return alda::raw::stream::return_<Stream>(
                                      fcppt::optional::object<Type>(std::move(_inner)));
                                })
                          : alda::raw::stream::return_<Stream>(fcppt::optional::object<Type>());
      });
}

template <typename Type, typename Adapted>
alda::raw::size_type needed_size(
    alda::raw::dispatch_type<alda::bindings::optional<Type, Adapted>>,
    alda::raw::element_type<alda::bindings::optional<Type, Adapted>> const &_opt_value)
{
  using binding = alda::bindings::optional<Type, Adapted>;

  using bool_type = typename binding::bool_type;

  constexpr alda::raw::size_type const ret(alda::raw::needed_size_static<bool_type>());

  return fcppt::optional::maybe(
      _opt_value,
      fcppt::const_(ret),
      [
#if defined(FCPPT_CONFIG_MSVC_COMPILER)
          ret
#endif
  ](Type const &_value) { return ret + alda::raw::needed_size<Adapted>(_value); });
}

}

#endif
