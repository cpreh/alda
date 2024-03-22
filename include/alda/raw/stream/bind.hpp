//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_BIND_HPP_INCLUDED
#define ALDA_RAW_STREAM_BIND_HPP_INCLUDED

#include <alda/raw/stream/error.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type, typename Function>
inline auto
bind(Type &&_value, Function const &_function) -> decltype(_function(std::forward<Type>(_value)))
  requires(!Stream::can_fail)
{
  return _function(std::forward<Type>(_value));
}

template <typename Stream, typename Type, typename Function>
inline auto
bind(fcppt::either::object<alda::raw::stream::error, Type> &&_value, Function const &_function)
    -> decltype(fcppt::either::bind(std::move(_value), _function))
  requires(Stream::can_fail)
{
  return fcppt::either::bind(std::move(_value), _function);
}
}

#endif
