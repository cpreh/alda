//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_DETAIL_COPY_N_HPP_INCLUDED
#define ALDA_RAW_DETAIL_COPY_N_HPP_INCLUDED

#include <alda/raw/const_pointer.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::detail
{

inline void copy_n(
    alda::raw::const_pointer const _src,
    alda::raw::size_type const _sz,
    alda::raw::pointer const _dest)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(_dest, _src, _sz);
FCPPT_PP_POP_WARNING
}

}

#endif
