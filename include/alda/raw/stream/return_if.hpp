//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STREAM_RETURN_IF_HPP_INCLUDED
#define ALDA_RAW_STREAM_RETURN_IF_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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
inline
typename
std::enable_if<
	Stream::can_fail,
	alda::raw::stream::result<
		Stream,
		Type
	>
>::type
return_if(
	alda::raw::stream::reference<
		Stream
	> _stream,
	alda::raw::element_type<
		Type
	> const &_value
)
{
	typedef
	alda::raw::stream::result<
		Stream,
		Type
	>
	result_type;

	return
		Stream::failed(
			_stream
		)
		?
			result_type()
		:
			result_type(
				_value
			)
		;

}

template<
	typename Stream,
	typename Type
>
inline
typename
std::enable_if<
	!Stream::can_fail,
	alda::raw::stream::result<
		Stream,
		Type
	>
>::type
return_if(
	alda::raw::stream::reference<
		Stream
	>,
	alda::raw::element_type<
		Type
	> const &_value
)
{
	return
		_value;
}

}
}
}

#endif
