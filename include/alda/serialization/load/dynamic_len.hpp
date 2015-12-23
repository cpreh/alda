//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LOAD_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/raw_container.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
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
		typedef
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
		>
		type;

		majutsu::raw::element_type<
			type
		> ret;

		typedef
		majutsu::raw::element_type<
			Length
		>
		length_type;

		majutsu::raw::size_type const length_sz(
			sizeof(
				length_type
			)
		);

		// At this point, the stream must be able to read its length
		length_type const sz(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::io::read<
					length_type
				>(
					_is,
					Length::endianness
				)
			)
		);

		alda::serialization::detail::raw_container vec(
			sz
			+
			length_sz
		);

		std::copy_n(
			fcppt::cast::to_char_ptr<
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
			fcppt::cast::to_char_ptr<
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
			majutsu::raw::make<
				type
			>(
				vec.data()
			);
	}
};

}
}

#endif
