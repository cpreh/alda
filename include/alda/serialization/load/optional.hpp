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
	typename
	alda::bindings::optional<
		T,
		A
	>::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef
		alda::bindings::optional<
			T,
			A
		> type;

		typedef typename type::bool_type::type bool_type;

		bool_type const is_set(
			*fcppt::io::read<
				bool_type
			>(
				_is,
				alda::endianness()
			)
		);

		typedef
		typename
		type::type
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
