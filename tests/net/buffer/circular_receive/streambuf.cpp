//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <fcppt/container/raw_vector/comparison.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/io/get.hpp>
#include <fcppt/io/optional_buffer.hpp>
#include <fcppt/io/read_chars.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <istream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace std
{

std::ostream &
operator<<(
	std::ostream &,
	fcppt::io::buffer const &
);

std::ostream &
operator<<(
	std::ostream &_stream,
	fcppt::io::buffer const &_buffer
)
{
	_stream << '(';

	for(
		char const val
		:
		_buffer
	)
		_stream << val << ',';

	return
		_stream << ')';
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	net_buffer_circular_receive_streambuf
)
{
FCPPT_PP_POP_WARNING

	alda::net::buffer::circular_receive::streambuf buffer{
		alda::net::buffer::max_receive_size{
			2u
		}
	};

	std::istream stream(
		&buffer
	);

	{
		alda::net::buffer::circular_receive::part const next_part{
			buffer.next_receive_part()
		};

		BOOST_REQUIRE_EQUAL(
			2u,
			next_part.size()
		);

		*next_part.begin() = '0';

		*std::next(
			next_part.begin()
		) = '1';

		buffer.bytes_received(
			2u
		);
	}

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		2
	);

	BOOST_REQUIRE_EQUAL(
		buffer.next_receive_part().size(),
		0u
	);

	typedef
	fcppt::optional::object<
		char
	>
	optional_char;

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'0'
		)
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'1'
		)
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char()
	);

	stream.clear();

	stream.unget();

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'1'
		)
	);

	{
		alda::net::buffer::circular_receive::part const next_part{
			buffer.next_receive_part()
		};

		BOOST_REQUIRE_EQUAL(
			1u,
			next_part.size()
		);

		*next_part.begin() = '2';

		buffer.bytes_received(
			1u
		);
	}

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		1
	);

	{
		alda::net::buffer::circular_receive::part const next_part{
			buffer.next_receive_part()
		};

		BOOST_REQUIRE_EQUAL(
			1u,
			next_part.size()
		);

		*next_part.begin() = '3';

		buffer.bytes_received(
			1u
		);
	}

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		2
	);

	stream.clear();

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'2'
		)
	);

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		1
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'3'
		)
	);

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		0
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char()
	);

	stream.clear();

	stream.unget();

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		1
	);

	stream.unget();

	BOOST_CHECK_EQUAL(
		buffer.showmanyc(),
		2
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'2'
		)
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char(
			'3'
		)
	);

	BOOST_REQUIRE_EQUAL(
		fcppt::io::get(
			stream
		),
		optional_char()
	);

	stream.clear();

	stream.unget();

	stream.unget();

	BOOST_CHECK_EQUAL(
		fcppt::io::read_chars(
			stream,
			2
		),
		fcppt::io::optional_buffer(
			fcppt::io::buffer{
				'2',
				'3'
			}
		)
	);
}
