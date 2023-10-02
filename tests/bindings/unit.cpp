//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/unit.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/either/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bidings::unit", "[alda]")
{
  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<alda::bindings::unit>(stream, fcppt::unit{});

  CHECK(stream.str().empty());

  CHECK(alda::serialization::read<alda::bindings::unit>(stream).has_success());
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
