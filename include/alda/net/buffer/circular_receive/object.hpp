//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_OBJECT_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_OBJECT_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/join.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);

	typedef fcppt::container::raw_vector<
		alda::net::value_type
	> impl_type;
public:
	typedef alda::net::size_type size_type;

	typedef alda::net::value_type *pointer;

	typedef alda::net::value_type const *const_pointer;

	ALDA_DETAIL_SYMBOL
	explicit
	object(
		alda::net::buffer::max_receive_size
	);

	ALDA_DETAIL_SYMBOL
	~object();

	// To which part can we receive next?
	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_receive::part
	next_receive_part();

	// Tell the buffer how much was actually read
	ALDA_DETAIL_SYMBOL
	void
	bytes_received(
		size_type
	);

	typedef boost::iterator_range<
		const_pointer
	> iterator_range;

	typedef boost::joined_range<
		iterator_range const,
		iterator_range const
	> joined_range;

	// the range that can be read
	ALDA_DETAIL_SYMBOL
	joined_range
	range() const;

	// remove already processed data
	ALDA_DETAIL_SYMBOL
	void
	erase(
		size_type
	);

	ALDA_DETAIL_SYMBOL
	size_type
	read_size() const;

	ALDA_DETAIL_SYMBOL
	size_type
	capacity() const;

	ALDA_DETAIL_SYMBOL
	void
	clear();
private:
	impl_type impl_;

	pointer
		begin_,
		end_;
};

}
}
}
}

#endif
