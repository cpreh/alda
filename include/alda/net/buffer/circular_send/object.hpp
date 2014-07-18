//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_OBJECT_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_OBJECT_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_send/boost_type.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef alda::net::size_type size_type;

	ALDA_DETAIL_SYMBOL
	explicit
	object(
		alda::net::buffer::max_send_size
	);

	ALDA_DETAIL_SYMBOL
	~object();

	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_send::boost_type::const_array_range const
	send_part() const;

	ALDA_DETAIL_SYMBOL
	void
	erase_front(
		alda::net::buffer::circular_send::object::size_type
	);

	ALDA_DETAIL_SYMBOL
	bool
	empty() const;

	ALDA_DETAIL_SYMBOL
	void
	clear();

	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_send::object::size_type
	space_left() const;

	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_send::boost_type &
	get();

	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_send::boost_type const &
	get() const;
private:
	alda::net::buffer::circular_send::boost_type impl_;
};

}
}
}
}

#endif
