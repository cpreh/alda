//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_GET_ERROR_HPP_INCLUDED
#define ALDA_RAW_STREAM_GET_ERROR_HPP_INCLUDED

#include <alda/raw/stream/error.hpp>
#include <fcppt/either/failure_opt.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type>
inline fcppt::optional::object<alda::raw::stream::error> get_error(Type const &)
  requires(!Stream::can_fail)
{
  return fcppt::optional::object<alda::raw::stream::error>{};
}

template <typename Stream, typename Type>
inline fcppt::optional::object<alda::raw::stream::error>
get_error(fcppt::either::object<alda::raw::stream::error, Type> &&_value)
  requires(Stream::can_fail)
{
  return fcppt::either::failure_opt(std::move(_value));
}
}

#endif
