//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_STREAMBUF_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_STREAMBUF_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <fcppt/cyclic_iterator_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/dynamic_array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_receive
{

class streambuf
:
	public std::streambuf
{
	FCPPT_NONCOPYABLE(
		streambuf
	);
public:
	ALDA_DETAIL_SYMBOL
	explicit
	streambuf(
		alda::net::buffer::max_receive_size
	);

	ALDA_DETAIL_SYMBOL
	~streambuf()
	override;

	/**
	\brief A contiguous memory range that can be written to
	*/
	ALDA_DETAIL_SYMBOL
	alda::net::buffer::circular_receive::part
	next_receive_part();

	/**
	\brief How many bytes have been written
	*/
	ALDA_DETAIL_SYMBOL
	void
	bytes_received(
		alda::net::size_type
	);

	ALDA_DETAIL_SYMBOL
	void
	clear();

	ALDA_DETAIL_SYMBOL
	std::streamsize
	showmanyc()
	override;
private:
	int_type
	uflow()
	override;

	int_type
	underflow()
	override;

	std::streamsize
	xsgetn(
		char_type *,
		std::streamsize
	)
	override;

	int_type
	pbackfail(
		int_type
	)
	override;

	typedef
	fcppt::container::dynamic_array<
		alda::net::value_type
	>
	raw_container;

	typedef
	raw_container::pointer
	iterator;

	typedef
	fcppt::cyclic_iterator<
		iterator
	>
	cyclic_iterator;

	cyclic_iterator
	iterator_group(
		iterator
	);

	raw_container impl_;

	iterator back_;

	iterator cur_;

	iterator end_;
};

}
}
}
}

#endif
