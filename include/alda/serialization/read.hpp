///          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_READ_HPP_INCLUDED
#define ALDA_SERIALIZATION_READ_HPP_INCLUDED

#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/serialization/istream.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Type
>
inline
alda::raw::stream::result<
	alda::raw::stream::istream,
	Type
>
read(
	alda::serialization::istream &_stream
)
{
	return
		alda::raw::make_generic<
			alda::raw::stream::istream,
			Type
		>(
			_stream
		);
}

}
}

#endif
