//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_TO_BUFFER_HPP_INCLUDED
#define ALDA_RAW_TO_BUFFER_HPP_INCLUDED

#include <alda/raw/buffer.hpp>
#include <alda/raw/data.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>


namespace alda
{
namespace raw
{

template<
	typename Type
>
alda::raw::buffer
to_buffer(
	alda::raw::element_type<
		Type
	> const &_value
)
{
	return
		fcppt::container::buffer::to_raw_vector(
			fcppt::container::buffer::read_from<
				fcppt::container::buffer::object<
					alda::raw::data
				>
			>(
				alda::raw::needed_size<
					Type
				>(
					_value
				),
				[
					&_value
				](
					alda::raw::buffer::pointer const _data,
					alda::raw::buffer::size_type const _size
				)
				{
					alda::raw::place<
						Type
					>(
						_value,
						_data
					);

					return
						_size;
				}
			)
		);
}

}
}

#endif
