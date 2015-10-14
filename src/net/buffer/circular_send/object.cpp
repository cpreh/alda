//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object.hpp>


alda::net::buffer::circular_send::object::object(
	alda::net::buffer::max_send_size const _buffer_max_size
)
:
	impl_(
		_buffer_max_size.get()
	)
{
}

alda::net::buffer::circular_send::object::~object()
{
}

alda::net::buffer::circular_send::boost_type::const_array_range
alda::net::buffer::circular_send::object::send_part() const
{
	return
		impl_.array_two().second == 0u
		?
			impl_.array_one()
		:
			impl_.array_two();
}

void
alda::net::buffer::circular_send::object::erase_front(
	alda::net::buffer::circular_send::object::size_type const _size
)
{
	impl_.erase(
		impl_.begin(),
		impl_.begin()
		+
		static_cast<
			alda::net::buffer::circular_send::boost_type::iterator::difference_type
		>(
			_size
		)
	);
}

bool
alda::net::buffer::circular_send::object::empty() const
{
	return
		impl_.empty();
}

void
alda::net::buffer::circular_send::object::clear()
{
	impl_.clear();
}

alda::net::buffer::circular_send::object::size_type
alda::net::buffer::circular_send::object::space_left() const
{
	return
		impl_.capacity()
		-
		impl_.size();
}

alda::net::buffer::circular_send::boost_type &
alda::net::buffer::circular_send::object::get()
{
	return
		impl_;
}

alda::net::buffer::circular_send::boost_type const &
alda::net::buffer::circular_send::object::get() const
{
	return
		impl_;
}
