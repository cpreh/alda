//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/optional.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/optional.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <bit>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>

namespace
{

using base_type = std::uint32_t;

using optional_type = fcppt::optional::object<base_type>;

using optional_binding =
    alda::bindings::optional<base_type, alda::bindings::unsigned_<base_type, std::endian::little>>;

using either_result_type = fcppt::either::object<alda::raw::stream::error, optional_type>;

}

FCPPT_CATCH_BEGIN

TEST_CASE("bindings::optional", "[alda]")
{
  {
    // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
    std::stringstream stream{};

    alda::serialization::write<optional_binding>(
        stream,
        optional_type{
            42U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        });

    either_result_type const result(
        alda::raw::make_generic<alda::raw::stream::istream, optional_binding>(stream));

    CHECK(
        result == either_result_type{optional_type{
                      42U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  }});
  }

  {
    // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
    std::stringstream stream{};

    alda::serialization::write<optional_binding>(stream, optional_type{});

    either_result_type const result(
        alda::raw::make_generic<alda::raw::stream::istream, optional_binding>(stream));

    CHECK(result == either_result_type{optional_type{}});
  }
}

FCPPT_CATCH_END
