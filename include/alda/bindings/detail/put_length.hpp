//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DETAIL_PUT_LENGTH_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_PUT_LENGTH_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/needed_size.hpp>
#include <majutsu/raw_pointer.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/cast/truncation_check.hpp>
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
void
put_length(
	majutsu::dispatch_type<
		Concept
	>,
	typename Concept::type const &_value,
	majutsu::raw_pointer &_memory
)
{
	typedef typename
	Concept::length_type length_type;

	length_type const dest_sz(
		fcppt::endianness::convert(
			fcppt::cast::truncation_check<
				length_type
			>(
				majutsu::needed_size<
					Concept
				>(
					_value
				)
			),
			alda::endianness()
		)
	);

	fcppt::algorithm::copy_n(
		reinterpret_cast<
			majutsu::const_raw_pointer
		>(
			&dest_sz
		),
		sizeof(length_type),
		_memory
	);

	_memory += sizeof(length_type);
}

}
}
}

#endif
