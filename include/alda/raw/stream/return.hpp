//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_RETURN_HPP_INCLUDED
#define ALDA_RAW_STREAM_RETURN_HPP_INCLUDED

#include <alda/raw/stream/error.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type>
inline Type return_(Type &&_value)
  requires(!Stream::can_fail)
{
  return std::forward<Type>(_value);
}

template <typename Stream, typename Type>
inline fcppt::either::object<alda::raw::stream::error, std::remove_cvref_t<Type>>
return_(Type &&_value)
  requires(Stream::can_fail)
{
  return fcppt::either::object<alda::raw::stream::error, std::remove_cvref_t<Type>>(
      std::forward<Type>(_value));
}
}

#endif
