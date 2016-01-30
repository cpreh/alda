//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_MAKE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_MAKE_HPP_INCLUDED

#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/serialization/detail/message_type.hpp>


namespace alda
{
namespace serialization
{
namespace length
{

template<
	typename TypeEnum
>
inline
alda::raw::size_type
make(
	alda::raw::size_type const _length
)
{
	return
		_length
		+
		alda::raw::static_size<
			alda::serialization::detail::message_type<
				TypeEnum
			>
		>::value;
}

}
}
}

#endif
