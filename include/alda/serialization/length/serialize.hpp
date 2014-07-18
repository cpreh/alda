//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_SERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_SERIALIZE_HPP_INCLUDED

#include <alda/message/base_fwd.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/serialize.hpp>
#include <alda/serialization/length/put.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <ostream>
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
serialize(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	alda::serialization::length::put<
		LengthType
	>(
		_stream,
		_message
	);

	alda::serialization::serialize(
		_stream,
		_message
	);
}

}
}
}

#endif
