//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_EXTRACT_MESSAGE_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_EXTRACT_MESSAGE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/message/optional_base_unique_ptr.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/length/deserialize.hpp>
#include <alda/serialization/length/remaining_size_function.hpp>


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
alda::message::optional_base_unique_ptr<
	TypeEnum
>
extract_message(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::net::buffer::circular_receive::streambuf &_data
)
{
	alda::serialization::istream stream{
		&_data
	};

	return
		alda::serialization::length::deserialize<
			LengthType
		>(
			_context,
			stream,
			alda::serialization::length::remaining_size_function{
				[
					&_data
				]{
					return
						_data.showmanyc();
				}
			}
		);
}

}
}
}
}

#endif
