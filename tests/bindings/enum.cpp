//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/enum.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <bit>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace
{

enum class test_enum
{
  value0,
  value1,
  fcppt_maximum = value1
};

using enum_binding =
    alda::bindings::enum_<test_enum, alda::bindings::unsigned_<std::uint8_t, std::endian::little>>;

using either_result_type = fcppt::either::object<alda::raw::stream::error, test_enum>;

}

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bindings::enum", "[alda]")
{
  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<enum_binding>(stream, test_enum::value1);

  either_result_type const result(
      alda::raw::make_generic<alda::raw::stream::istream, enum_binding>(stream));

  CHECK(result == either_result_type{test_enum::value1});

  stream.str("\x15");

  CHECK(alda::raw::make_generic<alda::raw::stream::istream, enum_binding>(stream).has_failure());
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
