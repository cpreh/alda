///          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_WRITE_RECORD_HPP_INCLUDED
#define ALDA_SERIALIZATION_WRITE_RECORD_HPP_INCLUDED

#include <alda/raw/record.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/write.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Types
>
inline
void
write_record(
	alda::serialization::ostream &_stream,
	alda::raw::record<
		Types
	> const &_record
)
{
	alda::serialization::write<
		alda::raw::record<
			Types
		>
	>(
		_stream,
		_record
	);
}

}
}

#endif
