//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_TO_BUFFER_HPP_INCLUDED
#define ALDA_RAW_RECORD_TO_BUFFER_HPP_INCLUDED

#include <alda/raw/buffer.hpp>
#include <alda/raw/to_buffer.hpp>
#include <alda/raw/record.hpp>


namespace alda
{
namespace raw
{

template<
	typename Types
>
inline
alda::raw::buffer
record_to_buffer(
	alda::raw::record<
		Types
	> const &_record
)
{
	return
		alda::raw::to_buffer<
			alda::raw::record<
				Types
			>
		>(
			_record
		);
}

}
}

#endif
