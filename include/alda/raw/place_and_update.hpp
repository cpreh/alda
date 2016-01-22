//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_PLACE_AND_UPDATE_HPP_INCLUDED
#define ALDA_RAW_PLACE_AND_UPDATE_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>


namespace alda
{
namespace raw
{

template<
	typename Type
>
inline
void
place_and_update(
	alda::raw::element_type<
		Type
	> const &_value,
	alda::raw::pointer &_data
)
{
	alda::raw::place<
		Type
	>(
		_value,
		_data
	);

	_data +=
		alda::raw::needed_size<
			Type
		>(
			_value
		);
}

}
}

#endif
