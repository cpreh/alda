//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_READ_HPP_INCLUDED
#define ALDA_RAW_STREAM_READ_HPP_INCLUDED

#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/stream/reference.hpp>

namespace alda::raw::stream
{

template <typename Stream>
inline void read(
    alda::raw::stream::reference<Stream> _stream,
    alda::raw::size_type const _size,
    alda::raw::pointer const _result)
{
  Stream::read(_stream, _size, _result);
}

}

#endif
