//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_STREAMBUF_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_STREAMBUF_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <ios>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

class streambuf
:
	public
		std::streambuf
{
	FCPPT_NONCOPYABLE(
		streambuf
	);

	typedef
	boost::circular_buffer<
		alda::net::value_type
	>
	impl_type;
public:
	typedef
	impl_type::size_type
	size_type;

	typedef
	impl_type::const_array_range
	const_array_range;

	ALDA_DETAIL_SYMBOL
	explicit
	streambuf(
		alda::net::buffer::max_send_size
	);

	ALDA_DETAIL_SYMBOL
	~streambuf()
	override;

	ALDA_DETAIL_SYMBOL
	size_type
	space_left() const;

	ALDA_DETAIL_SYMBOL
	const_array_range
	send_part() const;

	ALDA_DETAIL_SYMBOL
	void
	bytes_sent(
		size_type
	);

	ALDA_DETAIL_SYMBOL
	bool
	empty() const;

	ALDA_DETAIL_SYMBOL
	size_type
	capacity() const;

	ALDA_DETAIL_SYMBOL
	void
	clear();
private:
	std::streamsize
	xsputn(
		char_type const *,
		std::streamsize
	)
	override;

	int_type
	overflow(
		int_type
	)
	override;

	impl_type impl_;
};

}
}
}
}

#endif
