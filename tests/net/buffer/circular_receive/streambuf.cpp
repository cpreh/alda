//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/container/raw_vector/comparison.hpp>
#include <fcppt/io/buffer.hpp>
#include <fcppt/io/get.hpp>
#include <fcppt/io/optional_buffer.hpp>
#include <fcppt/io/read_chars.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
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
	return
		_stream
		<<
		fcppt::container::output(
			_buffer
		);
}

}

TEST_CASE(
	"net::buffer::circularr_eceive::streambuf",
	"[alda]"
)
{
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

		REQUIRE(
			2u
			==
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

	CHECK(
		buffer.showmanyc()
		==
		2
	);

	CHECK(
		buffer.next_receive_part().size()
		==
		0u
	);

	typedef
	fcppt::optional::object<
		char
	>
	optional_char;

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'0'
		)
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'1'
		)
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char()
	);

	stream.clear();

	stream.unget();

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'1'
		)
	);

	{
		alda::net::buffer::circular_receive::part const next_part{
			buffer.next_receive_part()
		};

		REQUIRE(
			1u
			==
			next_part.size()
		);

		*next_part.begin() = '2';

		buffer.bytes_received(
			1u
		);
	}

	CHECK(
		buffer.showmanyc()
		==
		1
	);

	{
		alda::net::buffer::circular_receive::part const next_part{
			buffer.next_receive_part()
		};

		REQUIRE(
			1u
			==
			next_part.size()
		);

		*next_part.begin() = '3';

		buffer.bytes_received(
			1u
		);
	}

	CHECK(
		buffer.showmanyc()
		==
		2
	);

	stream.clear();

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'2'
		)
	);

	CHECK(
		buffer.showmanyc()
		==
		1
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'3'
		)
	);

	CHECK(
		buffer.showmanyc()
		==
		0
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char()
	);

	stream.clear();

	stream.unget();

	CHECK(
		buffer.showmanyc()
		==
		1
	);

	stream.unget();

	CHECK(
		buffer.showmanyc()
		==
		2
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'2'
		)
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char(
			'3'
		)
	);

	REQUIRE(
		fcppt::io::get(
			stream
		)
		==
		optional_char()
	);

	stream.clear();

	stream.unget();

	stream.unget();

	CHECK(
		fcppt::io::read_chars(
			stream,
			2
		)
		==
		fcppt::io::optional_buffer(
			fcppt::io::buffer{
				'2',
				'3'
			}
		)
	);
}
