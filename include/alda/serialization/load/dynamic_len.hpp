//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LOAD_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/stream/istream.hpp>
#include <fcppt/assert/optional_error.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Type,
	typename Adapted,
	typename Length
>
struct load<
	alda::bindings::dynamic_len<
		Type,
		Adapted,
		Length
	>
>
{
	static
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
		>
	>
	get(
		alda::serialization::istream &_is
	)
	{
		return
			FCPPT_ASSERT_OPTIONAL_ERROR((
				majutsu::raw::make_generic<
					majutsu::raw::stream::istream,
					alda::bindings::dynamic_len<
						Type,
						Adapted,
						Length
					>
				>(
					_is
				)
			));
	}
};

}
}

#endif
