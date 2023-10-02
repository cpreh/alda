//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <alda/net/buffer/circular_receive/streambuf.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/container/raw_vector/comparison.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/container/raw_vector/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/io/buffer.hpp>
#include <fcppt/io/get.hpp>
#include <fcppt/io/optional_buffer.hpp>
#include <fcppt/io/read_chars.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <istream>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("net::buffer::circularr_eceive::streambuf", "[alda]")
{
  alda::net::buffer::circular_receive::streambuf buffer{alda::net::buffer::max_receive_size{2U}};

  std::istream stream(&buffer);

  {
    alda::net::buffer::circular_receive::part const next_part{buffer.next_receive_part()};

    REQUIRE(2U == next_part.size());

    *next_part.begin() = '0';

    // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
    *std::next(next_part.begin()) = '1';

    buffer.bytes_received(2U);
  }

  CHECK(buffer.showmanyc() == 2);

  CHECK(buffer.next_receive_part().empty());

  using optional_char = fcppt::optional::object<char>;

  REQUIRE(fcppt::io::get(stream) == optional_char('0'));

  REQUIRE(fcppt::io::get(stream) == optional_char('1'));

  REQUIRE(fcppt::io::get(stream) == optional_char());

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  stream.clear();

  stream.unget();

  REQUIRE(fcppt::io::get(stream) == optional_char('1'));

  {
    alda::net::buffer::circular_receive::part const next_part{buffer.next_receive_part()};

    REQUIRE(1U == next_part.size());

    *next_part.begin() = '2';

    buffer.bytes_received(1U);
  }

  CHECK(buffer.showmanyc() == 1);

  {
    alda::net::buffer::circular_receive::part const next_part{buffer.next_receive_part()};

    REQUIRE(1U == next_part.size());

    *next_part.begin() = '3';

    buffer.bytes_received(1U);
  }

  CHECK(buffer.showmanyc() == 2);

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  stream.clear();

  REQUIRE(fcppt::io::get(stream) == optional_char('2'));

  CHECK(buffer.showmanyc() == 1);

  REQUIRE(fcppt::io::get(stream) == optional_char('3'));

  CHECK(buffer.showmanyc() == 0);

  REQUIRE(fcppt::io::get(stream) == optional_char());

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  stream.clear();

  stream.unget();

  CHECK(buffer.showmanyc() == 1);

  stream.unget();

  CHECK(buffer.showmanyc() == 2);

  REQUIRE(fcppt::io::get(stream) == optional_char('2'));

  REQUIRE(fcppt::io::get(stream) == optional_char('3'));

  REQUIRE(fcppt::io::get(stream) == optional_char());

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  stream.clear();

  stream.unget();

  stream.unget();

  CHECK(
      fcppt::io::read_chars(stream, 2) == fcppt::io::optional_buffer(fcppt::io::buffer{'2', '3'}));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
