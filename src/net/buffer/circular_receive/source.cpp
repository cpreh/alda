//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/source.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <algorithm>
#include <ios>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::source::source(
	alda::net::buffer::circular_receive::object &_container
)
:
	container_(
		_container
	),
	read_count_(
		0
	)
{
}

std::streamsize
alda::net::buffer::circular_receive::source::read(
	char *const _dest,
	std::streamsize const _count
)
{
	alda::net::buffer::circular_receive::object::joined_range const range(
		container_.range()
	);

	std::streamsize const real_count(
		std::min(
			fcppt::cast::size<
				std::streamsize
			>(
				fcppt::cast::to_signed(
					range.size()
				)
			),
			_count
		)
	);

	if(
		real_count
		==
		0
	)
		return
			-1;

	std::copy_n(
		range.begin(),
		real_count,
		_dest
	);

	read_count_ +=
		real_count;

/*
	container_.erase(
		fcppt::cast::to_unsigned(
			real_count
		)
	);*/

	return
		real_count;
}

std::streampos
alda::net::buffer::circular_receive::source::seek(
	boost::iostreams::stream_offset const _offset,
	std::ios_base::seekdir const _dir
)
{
	// FIXME: Implement this properly
	// only here for tellg() to work!
	FCPPT_ASSERT_PRE(
		_offset == 0
	);

	FCPPT_ASSERT_PRE(
		_dir == std::ios_base::cur
	);

	return
		read_count_;
}
