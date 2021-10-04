//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_MESSAGE_TYPE_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_MESSAGE_TYPE_HPP_INCLUDED

#include <alda/smallest_uint.hpp>
#include <alda/bindings/enum.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/serialization/endianness.hpp>
#include <fcppt/enum/size.hpp>


namespace alda::serialization::detail
{

template<
	typename TypeEnum
>
using
message_type
=
alda::bindings::enum_<
	typename
	TypeEnum::type,
	alda::bindings::unsigned_<
		alda::smallest_uint<
			fcppt::enum_::size<
				typename
				TypeEnum::type
			>::value
		>,
		alda::serialization::endianness()
	>
>;

}

#endif
