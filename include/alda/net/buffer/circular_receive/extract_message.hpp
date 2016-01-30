//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_EXTRACT_MESSAGE_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_EXTRACT_MESSAGE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/source.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/length/deserialize.hpp>
#include <alda/serialization/length/remaining_size_function.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

template<
	typename LengthType,
	typename TypeEnum
>
fcppt::optional::object<
	alda::message::base_unique_ptr<
		TypeEnum
	>
>
extract_message(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::net::buffer::circular_receive::object &_data
)
{
	alda::serialization::length::remaining_size_function const remaining_size{
		[
			&_data
		]{
			return
				fcppt::cast::size<
					std::streamsize
				>(
					fcppt::cast::to_signed(
						_data.read_size()
					)
				);
		}
	};

	typedef
	boost::iostreams::stream_buffer<
		alda::net::buffer::circular_receive::source
	>
	stream_buf;

	stream_buf buf{
		alda::net::buffer::circular_receive::source{
			_data
		}
	};

	alda::serialization::istream stream{
		&buf
	};

	fcppt::optional::object<
		alda::message::base_unique_ptr<
			TypeEnum
		>
	> result(
		alda::serialization::length::deserialize<
			LengthType
		>(
			_context,
			stream,
			remaining_size
		)
	);

	_data.erase(
		fcppt::cast::to_unsigned(
			static_cast<
				std::streamoff
			>(
				stream.tellg()
			)
		)
	);

	return
		result;
}

}
}
}
}

#endif
