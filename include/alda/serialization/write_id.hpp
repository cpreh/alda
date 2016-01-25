//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_WRITE_ID_HPP_INCLUDED
#define ALDA_SERIALIZATION_WRITE_ID_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/write.hpp>
#include <alda/serialization/detail/message_type.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
inline
void
write_id(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	alda::serialization::write<
		alda::serialization::detail::message_type<
			TypeEnum
		>
	>(
		_stream,
		_message.type()
	);
}

}
}

#endif
