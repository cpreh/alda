//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LENGTH_EXTRACT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_EXTRACT_HPP_INCLUDED

#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/length/remaining_size_function.hpp>
#include <alda/serialization/length/detail/binding.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <istream>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace length
{

template<
	typename LengthType
>
typename
boost::enable_if<
	std::is_unsigned<
		LengthType
	>,
	fcppt::optional::object<
		LengthType
	>
>::type
extract(
	alda::serialization::istream &_stream,
	alda::serialization::length::remaining_size_function const &_remaining_size
)
{
	typedef
	fcppt::optional::object<
		LengthType
	>
	return_type;

	// in_avail can return showmanyc(), which can return -1
	return
		_remaining_size()
		<
		fcppt::cast::size<
			std::streamsize
		>(
			fcppt::cast::to_signed(
				sizeof(
					LengthType
				)
			)
		)
		?
			return_type()
		:
			alda::raw::make_generic<
				alda::raw::stream::istream,
				alda::serialization::length::detail::binding<
					LengthType
				>
			>(
				_stream
			)
		;
}

}
}
}

#endif
