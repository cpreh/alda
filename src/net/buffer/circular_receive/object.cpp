//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


alda::net::buffer::circular_receive::object::object(
	alda::net::buffer::max_receive_size const _max_size
)
:
	impl_(
		_max_size.get()
		+
		1u
	),
	begin_(
		impl_.data()
	),
	end_(
		impl_.data()
	)
{
}

alda::net::buffer::circular_receive::object::~object()
{
}

alda::net::buffer::circular_receive::part
alda::net::buffer::circular_receive::object::next_receive_part()
{
	return
		begin_
		<=
		end_
		?
			alda::net::buffer::circular_receive::part(
				end_,
				begin_
				==
				impl_.data()
				?
					std::prev(
						impl_.data_end()
					)
				:
					impl_.data_end()
			)
		:
			alda::net::buffer::circular_receive::part(
				end_,
				std::prev(
					begin_
				)
			);
}

void
alda::net::buffer::circular_receive::object::bytes_received(
	size_type const _size
)
{
	FCPPT_ASSERT_PRE(
		fcppt::cast::size<
			size_type
		>(
			fcppt::cast::to_unsigned(
				impl_.data_end()
				-
				end_
			)
		)
		>= _size
	);

	end_ +=
		_size;

	if(
		end_
		==
		impl_.data_end()
	)
		end_ =
			impl_.data();

	FCPPT_ASSERT_ERROR(
		begin_
		!=
		end_
	);
}

alda::net::buffer::circular_receive::object::joined_range
alda::net::buffer::circular_receive::object::range() const
{
	return
		begin_ <= end_
		?
			alda::net::buffer::circular_receive::object::joined_range(
				alda::net::buffer::circular_receive::object::iterator_range(
					const_pointer{
						begin_
					},
					const_pointer{
						end_
					}
				),
				alda::net::buffer::circular_receive::object::iterator_range()
			)
		:
			alda::net::buffer::circular_receive::object::joined_range(
				alda::net::buffer::circular_receive::object::iterator_range(
					const_pointer{
						begin_
					},
					impl_.data_end()
				),
				alda::net::buffer::circular_receive::object::iterator_range(
					impl_.data(),
					const_pointer{
						end_
					}
				)
			);
}

void
alda::net::buffer::circular_receive::object::erase(
	size_type const _size
)
{
	begin_ =
		impl_.data()
		+
		(
			(
				begin_
				-
				impl_.data()
				+
				fcppt::cast::to_signed(
					_size
				)
			)
			%
			fcppt::cast::to_signed(
				impl_.size()
			)
		);
}


alda::net::buffer::circular_receive::object::size_type
alda::net::buffer::circular_receive::object::read_size() const
{
	return
		fcppt::cast::size<
			size_type
		>(
			this->range().size()
		);
}

alda::net::buffer::circular_receive::object::size_type
alda::net::buffer::circular_receive::object::capacity() const
{
	return
		impl_.size()
		-
		1u;
}

void
alda::net::buffer::circular_receive::object::clear()
{
	begin_ =
		impl_.begin();

	end_ =
		impl_.begin();
}
