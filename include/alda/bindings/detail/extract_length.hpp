//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DETAIL_EXTRACT_LENGTH_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_EXTRACT_LENGTH_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/pointer.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/endianness/convert.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{
namespace detail
{

template<
	typename Concept
>
typename
Concept::length_type
extract_length(
	majutsu::dispatch_type<
		Concept
	>,
	majutsu::raw::const_pointer const _memory
)
{
	typedef
	typename
	Concept::length_type
	length_type;

	length_type ret;

	std::copy_n(
		_memory,
		sizeof(
			length_type
		),
		fcppt::cast::to_char_ptr<
			majutsu::raw::pointer
		>(
			&ret
		)
	);

	return
		fcppt::endianness::convert(
			ret,
			alda::endianness()
		);
}

}
}
}

#endif
