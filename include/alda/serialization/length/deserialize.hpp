//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_DESERIALIZE_HPP_INCLUDED

#include <alda/message/optional_base_unique_ptr.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/length/extract.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/optional/bind.hpp>
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
	alda::message::optional_base_unique_ptr<
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
	typedef
	alda::message::optional_base_unique_ptr<
		TypeEnum
	>
	result_type;

	return
		fcppt::optional::bind(
			alda::serialization::length::extract<
				LengthType
			>(
				_stream
			),
			[
				&_context,
				&_stream
			](
				LengthType const _length
			)
			{
				if(
					// in_avail can return -1
					_stream.rdbuf()->in_avail()
					<
					static_cast<
						std::streamsize
					>(
						_length
					)
				)
				{
					// TODO: should we putback the length instead?
					fcppt::algorithm::repeat(
						sizeof(
							LengthType
						),
						[
							&_stream
						]{
							_stream.unget();
						}
					);

					return
						result_type();
				}

				return
					result_type{
						alda::serialization::deserialize(
							_context,
							_stream
						)
					};
			}
		);
}

}
}
}

#endif
