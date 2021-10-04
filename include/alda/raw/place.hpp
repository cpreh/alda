//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_PLACE_HPP_INCLUDED
#define ALDA_RAW_PLACE_HPP_INCLUDED

#include <alda/raw/dispatch_value.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/pointer.hpp>


namespace alda::raw
{

template<
	typename Type
>
inline
void
place(
	alda::raw::element_type<
		Type
	> const &_value,
	alda::raw::pointer const _data
)
{
	return
		place(
			alda::raw::dispatch_value<
				Type
			>(),
			_value,
			_data
		);
}

}

#endif
