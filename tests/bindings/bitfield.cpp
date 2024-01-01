//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/bitfield.hpp>
#include <alda/raw/data.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/container/bitfield/object.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/math/ceil_div_static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <bit>
#include <limits>
#include <sstream>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bindings::bitfield", "[alda]")
{
  enum class test_enum
  {
    test1,
    test2,
    test3,
    fcppt_maximum = test3
  };

  using bitfield = fcppt::container::bitfield::object<test_enum, alda::raw::data>;

  using bitfield_binding = alda::bindings::bitfield<bitfield, std::endian::little>;

  static_assert(
      alda::raw::static_size<bitfield_binding>::value == // NOLINT(misc-redundant-expression)
      fcppt::math::ceil_div_static<
          alda::raw::size_type,
          3U, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          std::numeric_limits<alda::raw::data>::digits>::value);

  bitfield test(bitfield::null());

  test[test_enum::test2] = true;

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<bitfield_binding>(stream, test);

  CHECK(
      alda::serialization::read<bitfield_binding>(stream) ==
      fcppt::either::make_success<alda::raw::stream::error>(test));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
