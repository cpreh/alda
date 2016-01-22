///          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_WRITE_HPP_INCLUDED
#define ALDA_SERIALIZATION_WRITE_HPP_INCLUDED

#include <alda/raw/record_fwd.hpp>
#include <alda/raw/to_buffer.hpp>
#include <alda/serialization/buffer_to_stream.hpp>
#include <alda/serialization/ostream.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Types
>
void
write(
	alda::serialization::ostream &_stream,
	alda::raw::record<
		Types
	> const &_record
)
{
	alda::serialization::buffer_to_stream(
		_stream,
		alda::raw::to_buffer(
			_record
		)
	);
}

}
}

#endif
