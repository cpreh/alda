//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_TO_BUFFER_HPP_INCLUDED
#define ALDA_RAW_TO_BUFFER_HPP_INCLUDED

#include <alda/raw/buffer.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/record.hpp>


namespace alda
{
namespace raw
{

template<
	typename Types
>
alda::raw::buffer
to_buffer(
	alda::raw::record<
		Types
	> const &_record
)
{
	alda::raw::buffer temp_buffer;

	temp_buffer.resize_uninitialized(
		alda::raw::needed_size<
			alda::raw::record<
				Types
			>
		>(
			_record
		)
	);

	alda::raw::place<
		alda::raw::record<
			Types
		>
	>(
		_record,
		temp_buffer.data()
	);

	return
		temp_buffer;
}

}
}

#endif
