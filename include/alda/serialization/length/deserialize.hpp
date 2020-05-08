//          Copyright Carl Philipp Reh 2016.
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
#include <alda/serialization/length/remaining_size_function.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <ios>
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
alda::message::optional_base_unique_ptr<
	TypeEnum
>
deserialize(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::serialization::istream &_stream,
	alda::serialization::length::remaining_size_function const &_remaining_size
)
{
	static_assert(
		std::is_unsigned_v<
			LengthType
		>
	);

	using
	result_type
	=
	alda::message::optional_base_unique_ptr<
		TypeEnum
	>;

	return
		fcppt::optional::bind(
			alda::serialization::length::extract<
				LengthType
			>(
				_stream,
				_remaining_size
			),
			[
				&_context,
				&_stream,
				&_remaining_size
			](
				LengthType const _length
			)
			{
				if(
					_remaining_size()
					<
					fcppt::cast::size<
						std::streamsize
					>(
						fcppt::cast::to_signed(
							_length
						)
					)
				)
				{
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
