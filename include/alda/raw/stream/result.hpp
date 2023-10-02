//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_RAW_STREAM_RESULT_HPP_INCLUDED
#define ALDA_RAW_STREAM_RESULT_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/stream/error.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{

template <typename Stream, typename Type>
using result = std::conditional_t<
    Stream::can_fail,
    fcppt::either::object<alda::raw::stream::error, alda::raw::element_type<Type>>,
    alda::raw::element_type<Type>>;

}

#endif
