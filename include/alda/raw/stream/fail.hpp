//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_FAIL_HPP_INCLUDED
#define ALDA_RAW_STREAM_FAIL_HPP_INCLUDED

#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/failure.hpp>
#include <alda/raw/stream/result.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type>
[[noreturn]] inline alda::raw::stream::result<Stream, Type> fail(alda::raw::stream::error const _error)
  requires(!Stream::can_fail)
{
  throw alda::raw::stream::failure{_error};
}

template <typename Stream, typename Type>
inline alda::raw::stream::result<Stream, Type> fail(alda::raw::stream::error const _error)
  requires(Stream::can_fail)
{
  return alda::raw::stream::result<Stream, Type>{_error};
}
}

#endif
