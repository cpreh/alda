//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_PUT_MESSAGE_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_PUT_MESSAGE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/buffer/circular_send/sink.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/length/make.hpp>
#include <alda/serialization/length/serialize.hpp>
#include <alda/raw/size_type.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/preprocessor/warn_unused_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

template<
	typename LengthType,
	typename TypeEnum
>
bool
put_message(
	alda::message::base<
		TypeEnum
	> const &,
	alda::net::buffer::circular_send::object &
)
FCPPT_PP_WARN_UNUSED_RESULT;

}
}
}
}

template<
	typename LengthType,
	typename TypeEnum
>
bool
alda::net::buffer::circular_send::put_message(
	alda::message::base<
		TypeEnum
	> const &_message,
	alda::net::buffer::circular_send::object &_buffer
)
{
	alda::raw::size_type const size(
		alda::serialization::length::make<
			TypeEnum
		>(
			_message.size()
		)
	);

	FCPPT_ASSERT_PRE_MESSAGE(
		_buffer.get().capacity()
		>=
		size,
		(
			fcppt::format(
				FCPPT_TEXT("Send message size %1% is too big for the buffer!")
			)
			% size
		).str()
	);

	if(
		size
		>
		_buffer.space_left()
	)
		return
			false;

	boost::iostreams::stream_buffer<
		alda::net::buffer::circular_send::sink
	> stream_buf(
		alda::net::buffer::circular_send::sink{
			_buffer
		}
	);

	alda::serialization::ostream stream(
		&stream_buf
	);

	alda::serialization::length::serialize<
		LengthType
	>(
		stream,
		_message
	);

	FCPPT_ASSERT_ERROR(
		!stream.fail()
	);

	return
		true;
}

#endif
