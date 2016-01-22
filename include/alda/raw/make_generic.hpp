//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_MAKE_GENERIC_HPP_INCLUDED
#define ALDA_RAW_MAKE_GENERIC_HPP_INCLUDED

#include <alda/raw/dispatch_value.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>


namespace alda
{
namespace raw
{

template<
	typename Stream,
	typename Type
>
inline
alda::raw::stream::result<
	Stream,
	Type
>
make_generic(
	alda::raw::stream::reference<
		Stream
	> _stream
)
{
	return
		make_generic(
			alda::raw::dispatch_value<
				Type
			>(),
			alda::raw::dispatch_value<
				Stream
			>(),
			_stream
		);
}

}
}

#endif
