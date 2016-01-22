//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_WRITE_ID_HPP_INCLUDED
#define ALDA_SERIALIZATION_WRITE_ID_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/serialization/endianness.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/io/write.hpp>


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
	fcppt::io::write(
		_stream,
		fcppt::cast::enum_to_int<
			alda::serialization::detail::message_int_type
		>(
			_message.type()
		),
		alda::serialization::endianness()
	);
}

}
}

#endif
