//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_SERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_SERIALIZE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/raw/buffer.hpp>
#include <alda/serialization/buffer_to_stream.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/write_id.hpp>
#include <alda/serialization/length/put.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda::serialization::length
{

template<
	typename LengthType,
	typename TypeEnum
>
void
serialize(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	static_assert(
		std::is_unsigned_v<
			LengthType
		>
	);

	alda::raw::buffer const buffer(
		_message.to_buffer()
	);

	alda::serialization::length::put<
		TypeEnum,
		LengthType
	>(
		_stream,
		buffer.size()
	);

	alda::serialization::write_id(
		_stream,
		_message
	);

	alda::serialization::buffer_to_stream(
		_stream,
		buffer
	);
}

}

#endif
