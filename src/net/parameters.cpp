//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/io_service_wrapper_fwd.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>


alda::net::parameters::parameters(
	alda::net::io_service_wrapper const &_io_service_wrapper,
	alda::net::buffer::max_send_size const _max_send_size,
	alda::net::buffer::max_receive_size const _max_receive_size
)
:
	io_service_wrapper_(
		_io_service_wrapper
	),
	max_send_size_(
		_max_send_size
	),
	max_receive_size_(
		_max_receive_size
	)
{
}

alda::net::io_service_wrapper const &
alda::net::parameters::io_service_wrapper() const
{
	return io_service_wrapper_;
}

alda::net::buffer::max_send_size const
alda::net::parameters::max_send_size() const
{
	return max_send_size_;
}

alda::net::buffer::max_receive_size const
alda::net::parameters::max_receive_size() const
{
	return max_receive_size_;
}
