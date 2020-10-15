//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::part::part(
	pointer const _begin, // NOLINT(misc-misplaced-const)
	pointer const _end // NOLINT(misc-misplaced-const)
)
:
	begin_(
		_begin
	),
	end_(
		_end
	)
{
}

alda::net::buffer::circular_receive::part::pointer
alda::net::buffer::circular_receive::part::begin() const
{
	return
		begin_;
}

alda::net::buffer::circular_receive::part::pointer
alda::net::buffer::circular_receive::part::end() const
{
	return
		end_;
}

alda::net::buffer::circular_receive::part::size_type
alda::net::buffer::circular_receive::part::size() const
{
	return
		fcppt::cast::size<
			alda::net::buffer::circular_receive::part::size_type
		>(
			fcppt::cast::to_unsigned(
				std::distance(
					this->begin(),
					this->end()
				)
			)
		);
}

bool
alda::net::buffer::circular_receive::part::empty() const
{
	return
		this->size()
		==
		0U;
}
