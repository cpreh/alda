//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LOAD_OPTIONAL_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_OPTIONAL_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/raw/element_type.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/io/read.hpp>


namespace alda
{
namespace serialization
{

template<
	typename T,
	typename A
>
struct load<
	alda::bindings::optional<
		T,
		A
	>
>
{
	static
	majutsu::raw::element_type<
		alda::bindings::optional<
			T,
			A
		>
	>
	get(
		alda::serialization::istream &_is
	)
	{
		typedef
		alda::bindings::optional<
			T,
			A
		> type;

		typedef
		majutsu::raw::element_type<
			typename
			type::bool_type
		>
		bool_type;

		bool_type const is_set(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::io::read<
					bool_type
				>(
					_is,
					alda::endianness()
				)
			)
		);

		typedef
		majutsu::raw::element_type<
			type
		>
		optional_type;

		return
			is_set
			?
				optional_type(
					alda::serialization::load<
						A
					>::get(
						_is
					)
				)
			:
				optional_type()
			;
	}
};

}
}

#endif
