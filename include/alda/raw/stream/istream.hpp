//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STREAM_ISTREAM_HPP_INCLUDED
#define ALDA_RAW_STREAM_ISTREAM_HPP_INCLUDED

#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/stream/istream_fwd.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace stream
{

struct istream
{
	typedef
	std::istream &
	reference;

	static
	inline
	void
	read(
		alda::raw::stream::istream::reference _stream,
		alda::raw::size_type const _size,
		alda::raw::pointer const _result
	)
	{
		_stream.read(
			fcppt::cast::to_char_ptr<
				std::istream::char_type *
			>(
				_result
			),
			fcppt::cast::size<
				std::streamsize
			>(
				fcppt::cast::to_signed(
					_size
				)
			)
		);
	}

	static
	constexpr
	bool const
	can_fail = true;

	static
	inline
	bool
	failed(
		alda::raw::stream::istream::reference _stream
	)
	{
		return
			_stream.fail();
	}
};

}
}
}

#endif
