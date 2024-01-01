//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_FAIL_HPP_INCLUDED
#define ALDA_RAW_STREAM_FAIL_HPP_INCLUDED

#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/failure.hpp>
#include <alda/raw/stream/result.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <typeinfo> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type>
[[noreturn]] inline
    std::enable_if_t<!Stream::can_fail, alda::raw::stream::result<Stream, Type>>
    fail(fcppt::string const &_error)
{
  throw alda::raw::stream::failure{
      FCPPT_TEXT("Type ") + fcppt::from_std_string(fcppt::type_name_from_info(typeid(Type))) +
      FCPPT_TEXT(": ") + _error};
}

template <typename Stream, typename Type>
inline std::enable_if_t<Stream::can_fail, alda::raw::stream::result<Stream, Type>>
fail(fcppt::string const &_error)
{
  return alda::raw::stream::result<Stream, Type>(alda::raw::stream::error{_error});
}

}

#endif
