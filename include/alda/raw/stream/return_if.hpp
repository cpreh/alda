//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_RETURN_IF_HPP_INCLUDED
#define ALDA_RAW_STREAM_RETURN_IF_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/stream/fail.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/text.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type>
inline alda::raw::stream::result<Stream, Type>
return_if(alda::raw::stream::reference<Stream> _stream, alda::raw::element_type<Type> const &_value)
  requires(Stream::can_fail)
{
  return Stream::failed(_stream)
             ? alda::raw::stream::fail<Stream, Type>(FCPPT_TEXT("Stream failed"))
             : alda::raw::stream::return_<Stream>(_value);
}

template <typename Stream, typename Type>
inline alda::raw::stream::result<Stream, Type>
return_if(alda::raw::stream::reference<Stream>, alda::raw::element_type<Type> const &_value)
  requires(!Stream::can_fail)
{
  return _value;
}

}

#endif
