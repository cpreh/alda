//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/size_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <fcppt/cyclic_iterator_impl.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <ios>
#include <iterator>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::streambuf::streambuf(
	alda::net::buffer::max_receive_size const _max_receive_size
)
:
	std::streambuf(),
	impl_(
		_max_receive_size.get()
		+
		1u
	),
	back_{
		impl_.data()
	},
	cur_{
		impl_.data()
	},
	end_{
		impl_.data()
	}
{
}

alda::net::buffer::circular_receive::streambuf::~streambuf()
{
}

alda::net::buffer::circular_receive::part
alda::net::buffer::circular_receive::streambuf::next_receive_part()
{
	iterator const last(
		std::prev(
			this->iterator_group(
				cur_
			)
		).get()
	);

	return
		end_
		<=
		last
		?
			alda::net::buffer::circular_receive::part{
				end_,
				last
			}
		:
			alda::net::buffer::circular_receive::part{
				end_,
				impl_.data_end()
			}
		;
}

void
alda::net::buffer::circular_receive::streambuf::bytes_received(
	alda::net::size_type const _size
)
{
	back_ =
		cur_;

	end_ =
		(
			this->iterator_group(
				end_
			)
			+
			fcppt::cast::to_signed(
				_size
			)
		).get();
}

void
alda::net::buffer::circular_receive::streambuf::clear()
{
	back_ =
		impl_.data();

	cur_ =
		impl_.data();

	end_ =
		impl_.data();
}

std::streamsize
alda::net::buffer::circular_receive::streambuf::showmanyc()
{
	std::streamsize diff{
		end_
		-
		cur_
	};

	if(
		diff
		<
		0
	)
		diff +=
			fcppt::cast::to_signed(
				impl_.size()
			);

	return
		diff;
}

alda::net::buffer::circular_receive::streambuf::int_type
alda::net::buffer::circular_receive::streambuf::uflow()
{
	int_type const result(
		this->underflow()
	);

	if(
		!traits_type::eq_int_type(
			result,
			traits_type::eof()
		)
	)
		cur_ =
			std::next(
				this->iterator_group(
					cur_
				)
			).get();

	return
		result;
}

alda::net::buffer::circular_receive::streambuf::int_type
alda::net::buffer::circular_receive::streambuf::underflow()
{
	return
		cur_
		==
		end_
		?
			traits_type::eof()
		:
			traits_type::to_int_type(
				*cur_
			)
		;
}

std::streamsize
alda::net::buffer::circular_receive::streambuf::xsgetn(
	char_type *const _dest,
	std::streamsize const _sz
)
{
	std::streamsize const to_copy{
		std::min(
			_sz,
			this->showmanyc()
		)
	};

	cyclic_iterator const beg{
		this->iterator_group(
			cur_
		)
	};

	cyclic_iterator const end{
		beg
		+
		to_copy
	};

	std::transform(
		beg,
		end,
		_dest,
		[](
			alda::net::value_type const _val
		)
		-> char_type
		{
			return
				_val;
		}
	);

	cur_ =
		end.get();

	return
		to_copy;
}

alda::net::buffer::circular_receive::streambuf::int_type
alda::net::buffer::circular_receive::streambuf::pbackfail(
	int_type const _c
)
{
	if(
		back_
		==
		cur_
	)
		return
			traits_type::eof();

	cur_ =
		std::prev(
			this->iterator_group(
				cur_
			)
		).get();

	if(
		!traits_type::eq_int_type(
			_c,
			traits_type::eof()
		)
	)
		*cur_ =
			traits_type::to_char_type(
				_c
			);

	return
		0;
}

alda::net::buffer::circular_receive::streambuf::cyclic_iterator
alda::net::buffer::circular_receive::streambuf::iterator_group(
	iterator const _it
)
{
	return
		cyclic_iterator{
			_it,
			cyclic_iterator::boundary{
				impl_.data(),
				impl_.data_end()
			}
		};
}
