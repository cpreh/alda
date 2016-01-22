//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/serialization/endianness.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/io/write.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace length
{

template<
	typename LengthType
>
typename
boost::enable_if<
	std::is_unsigned<
		LengthType
	>,
	void
>::type
put(
	alda::serialization::ostream &_stream,
	alda::raw::size_type const _length
)
{
	static_assert(
		sizeof(
			alda::raw::size_type
		)
		>=
		sizeof(
			LengthType
		),
		"The LengthType cannot exceed alda::raw::size_type"
	);

	alda::raw::size_type const result{
		_length
		+
		sizeof(
			alda::serialization::detail::message_int_type
		)
	};

	if(
		result
		<
		_length
	)
		throw
			alda::exception{
				FCPPT_TEXT("Length overflowed")
			};

	fcppt::io::write(
		_stream,
		fcppt::cast::truncation_check<
			LengthType
		>(
			result
		),
		alda::serialization::endianness()
	);
}

}
}
}

#endif
