//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/duration.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <bit>
#include <cstdint>
#include <ratio>
#include <sstream>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bindings::duration", "[alda]")
{
  using int_binding = alda::bindings::unsigned_<std::uint32_t, std::endian::little>;

  using duration_binding = alda::bindings::duration<int_binding, std::milli>;

  static_assert(
      alda::raw::static_size<duration_binding>::value == // NOLINT(misc-redundant-expression)
      alda::raw::static_size<int_binding>::value);

  using duration = alda::raw::element_type<duration_binding>;

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<duration_binding>(
      stream,
      // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
      duration{
          10U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      });

  CHECK(
      alda::serialization::read<duration_binding>(stream) ==
      fcppt::either::make_success<alda::raw::stream::error>(
          // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
          duration{
              // NOLINT(fuchsia-default-arguments-calls)
              10U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          }));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
