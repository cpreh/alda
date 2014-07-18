//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DETAIL_EXTRACT_LENGTH_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_EXTRACT_LENGTH_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/raw_pointer.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/endianness/convert.hpp>


namespace alda
{
namespace bindings
{
namespace detail
{

template<
	typename Concept
>
typename Concept::length_type
extract_length(
	Concept const *,
	majutsu::const_raw_pointer const _memory
)
{
	typedef typename Concept::length_type length_type;

	length_type ret;

	fcppt::algorithm::copy_n(
		_memory,
		sizeof(length_type),
		reinterpret_cast<
			majutsu::raw_pointer
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
