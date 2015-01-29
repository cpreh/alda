//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LOAD_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/raw_container.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/make.hpp>
#include <majutsu/size_type.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename T,
	typename A
>
struct load<
	alda::bindings::dynamic_len<
		T,
		A
	>
>
{
	static
	typename
	alda::bindings::dynamic_len<
		T,
		A
	>::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef
		alda::bindings::dynamic_len<
			T,
			A
		> type;

		typename type::type ret;

		majutsu::size_type const length_sz(
			sizeof(
				typename type::length_type
			)
		);

		typedef typename type::length_type length_type;

		// At this point, the stream must be able to read its length
		length_type const sz(
			*fcppt::io::read<
				length_type
			>(
				_is,
				alda::endianness()
			)
		);

		alda::serialization::detail::raw_container vec(
			sz
			+
			length_sz
		);

		std::copy_n(
			reinterpret_cast<
				alda::serialization::detail::raw_container::const_pointer
			>(
				&sz
			),
			sizeof(
				length_type
			),
			vec.data()
		);

		_is.read(
			reinterpret_cast<
				char *
			>(
				vec.data()
				+
				length_sz
			),
			static_cast<
				std::streamsize
			>(
				sz - length_sz
			)
		);

		return
			majutsu::make<
				type
			>(
				vec.data()
			);
	}
};

}
}

#endif
