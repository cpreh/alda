///          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_STATIC_BUFFER_TO_STREAM_HPP_INCLUDED
#define ALDA_SERIALIZATION_STATIC_BUFFER_TO_STREAM_HPP_INCLUDED

#include <alda/raw/static_buffer.hpp>
#include <alda/serialization/ostream.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Type
>
inline
void
static_buffer_to_stream(
	alda::serialization::ostream &_stream,
	alda::raw::static_buffer<
		Type
	> const &_buffer
)
{
	_stream.write(
		fcppt::cast::to_char_ptr<
			alda::serialization::ostream::char_type const *
		>(
			_buffer.data()
		),
		fcppt::cast::size<
			std::streamsize
		>(
			fcppt::cast::to_signed(
				_buffer.size()
			)
		)
	);
}

}
}

#endif
