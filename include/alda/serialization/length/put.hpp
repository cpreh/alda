//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_PUT_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/write.hpp>
#include <alda/serialization/length/make.hpp>
#include <alda/serialization/length/detail/binding.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda::serialization::length
{

template<
	typename TypeEnum,
	typename LengthType
>
inline
void
put(
	alda::serialization::ostream &_stream,
	alda::raw::size_type const _length
)
{
	static_assert(
		std::is_unsigned_v<
			LengthType
		>
	);

	alda::serialization::write<
		alda::serialization::length::detail::binding<
			LengthType
		>
	>(
		_stream,
		fcppt::optional::to_exception(
			fcppt::cast::truncation_check<
				LengthType
			>(
				alda::serialization::length::make<
					TypeEnum
				>(
					_length
				)
			),
			[]{
				return
					alda::exception{
						FCPPT_TEXT("length::put: size too large")
					};
			}
		)
	);
}

}

#endif
