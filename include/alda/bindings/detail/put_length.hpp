//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DETAIL_PUT_LENGTH_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_PUT_LENGTH_HPP_INCLUDED

#include <alda//endianness.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/pointer.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/truncation_check.hpp>
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
void
put_length(
	majutsu::dispatch_type<
		Concept
	>,
	majutsu::raw::element_type<
		Concept
	> const &_value,
	majutsu::raw::pointer &_memory
)
{
	typedef
	typename
	Concept::length_type
	length_type;

	length_type const dest_sz(
		fcppt::endianness::convert(
			fcppt::cast::truncation_check<
				length_type
			>(
				majutsu::raw::needed_size<
					Concept
				>(
					_value
				)
			),
			alda::endianness()
		)
	);

	std::copy_n(
		fcppt::cast::to_char_ptr<
			majutsu::raw::const_pointer
		>(
			&dest_sz
		),
		sizeof(
			length_type
		),
		_memory
	);

	_memory +=
		sizeof(
			length_type
		);
}

}
}
}

#endif
