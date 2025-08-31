//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_MEMORY_HPP_INCLUDED
#define ALDA_RAW_STREAM_MEMORY_HPP_INCLUDED

#include <alda/raw/const_pointer.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/detail/copy_n.hpp>
#include <alda/raw/stream/memory_fwd.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace alda::raw::stream
{

struct memory
{
  using reference = alda::raw::const_pointer &;

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  static void read(
      alda::raw::stream::memory::reference _stream,
      alda::raw::size_type const _size,
      alda::raw::pointer const _result)
  {
    alda::raw::detail::copy_n(_stream, _size, _result);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    _stream += _size;
  }

  FCPPT_PP_POP_WARNING

  static constexpr bool const can_fail = false;
};

}

#endif
