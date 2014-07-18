//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/serialization/ostream.hpp>
#include <fcppt/io/write.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <exception>
#include <limits>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace length
{

template<
	typename LengthType,
	typename TypeEnum
>
typename boost::enable_if<
	std::is_unsigned<
		LengthType
	>,
	void
>::type
put(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	typedef alda::message::base<
		TypeEnum
	> message_base;

	typedef typename message_base::size_type message_size_type;

	static_assert(
		sizeof(
			message_size_type
		)
		>=
		sizeof(
			LengthType
		),
		"The LengthType cannot exceed the message_size_type"
	);

	if(
		static_cast<
			message_size_type
		>(
			std::numeric_limits<
				LengthType
			>::max()
		)
		<=
		_message.size()
	)
		std::terminate();

	fcppt::io::write(
		_stream,
		static_cast<
			LengthType
		>(
			_message.size()
		),
		alda::endianness()
	);
}

}
}
}

#endif
