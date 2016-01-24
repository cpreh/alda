//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STREAM_FAIL_HPP_INCLUDED
#define ALDA_RAW_STREAM_FAIL_HPP_INCLUDED

#include <alda/raw/stream/failure.hpp>
#include <alda/raw/stream/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace stream
{

template<
	typename Stream,
	typename Type
>
[[noreturn]]
inline
typename
std::enable_if<
	!Stream::can_fail,
	alda::raw::stream::result<
		Stream,
		Type
	>
>::type
fail()
{
	throw
		alda::raw::stream::failure();
}

template<
	typename Stream,
	typename Type
>
inline
typename
std::enable_if<
	Stream::can_fail,
	alda::raw::stream::result<
		Stream,
		Type
	>
>::type
fail()
{
	return
		alda::raw::stream::result<
			Stream,
			Type
		>();
}

}
}
}

#endif
