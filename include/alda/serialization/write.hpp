///          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_WRITE_HPP_INCLUDED
#define ALDA_SERIALIZATION_WRITE_HPP_INCLUDED

#include <alda/raw/element_type.hpp>
#include <alda/raw/is_static_size.hpp>
#include <alda/raw/to_buffer.hpp>
#include <alda/raw/to_static_buffer.hpp>
#include <alda/serialization/buffer_to_stream.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/static_buffer_to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Type
>
inline
typename
boost::enable_if<
	alda::raw::is_static_size<
		Type
	>,
	void
>::type
write(
	alda::serialization::ostream &_stream,
	alda::raw::element_type<
		Type
	> const &_value
)
{
	alda::serialization::static_buffer_to_stream<
		Type
	>(
		_stream,
		alda::raw::to_static_buffer<
			Type
		>(
			_value
		)
	);
}

template<
	typename Type
>
inline
typename
boost::disable_if<
	alda::raw::is_static_size<
		Type
	>,
	void
>::type
write(
	alda::serialization::ostream &_stream,
	alda::raw::element_type<
		Type
	> const &_value
)
{
	alda::serialization::buffer_to_stream(
		_stream,
		alda::raw::to_buffer<
			Type
		>(
			_value
		)
	);
}

}
}

#endif
