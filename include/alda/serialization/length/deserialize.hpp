//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_DESERIALIZE_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/length/extract.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <cstddef>
#include <iosfwd>
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
	alda::message::base_unique_ptr<
		TypeEnum
	>
>::type
deserialize(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::serialization::istream &_stream
)
{
	typedef fcppt::optional<
		LengthType
	> length_result;

	length_result const length(
		alda::serialization::length::extract<
			LengthType
		>(
			_stream
		)
	);

	typedef alda::message::base_unique_ptr<
		TypeEnum
	> result_type;

	if(
		!length
	)
		return
			result_type();

	if(
		// in_avail can return -1
		_stream.rdbuf()->in_avail()
		<
		static_cast<
			std::streamsize
		>(
			*length
		)
	)
	{
		// TODO: should be putback the length instead?
		for(
			std::size_t i = 0;
			i < sizeof(LengthType);
			++i
		)
			_stream.unget();

		return
			result_type();
	}

	return
		alda::serialization::deserialize(
			_context,
			_stream
		);
}

}
}
}

#endif
