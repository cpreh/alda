//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LOAD_STATIC_SIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_STATIC_SIZE_HPP_INCLUDED

#include <alda/serialization/istream.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/raw/data.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/is_static_size.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <array>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Type
>
struct load<
	Type,
	typename
	boost::enable_if<
		majutsu::raw::is_static_size<
			Type
		>
	>::type
>
{
	static
	majutsu::raw::element_type<
		Type
	>
	get(
		alda::serialization::istream &_is
	)
	{
		typedef std::array<
			majutsu::raw::data,
			majutsu::raw::static_size<
				Type
			>::value
		> buffer_type;

		buffer_type buffer;

		_is.read(
			fcppt::cast::to_char_ptr<
				char *
			>(
				buffer.data()
			),
			static_cast<
				std::streamsize
			>(
				buffer.size()
			)
		);

		return
			majutsu::raw::make<
				Type
			>(
				buffer.data()
			);
	}
};

}
}

#endif
