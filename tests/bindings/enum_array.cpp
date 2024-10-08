//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/enum_array.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/enum/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <bit>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>

namespace
{
enum class my_enum : std::uint8_t
{
  enum1,
  enum2,
  enum3
};
}
FCPPT_ENUM_DEFINE_MAX_VALUE(my_enum::enum3);
namespace
{
using int_type = unsigned;

using array = fcppt::enum_::array<my_enum, int_type>;

using unsigned_binding = alda::bindings::unsigned_<int_type, std::endian::little>;

using array_binding = alda::bindings::enum_array<array, unsigned_binding>;

static_assert(
    alda::raw::static_size<array_binding>::value ==
    alda::raw::static_size<unsigned_binding>::value * fcppt::enum_::size<my_enum>::value);

using either_result_type = fcppt::either::object<alda::raw::stream::error, array>;

}

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bdings::enum_array", "[alda]")
{
  auto const test(fcppt::enum_::array_init<array>(
      [](my_enum const _element) { return fcppt::cast::enum_to_int<int_type>(_element); }));

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<array_binding>(stream, test);

  CHECK(
      alda::serialization::read<array_binding>(stream) ==
      fcppt::either::make_success<alda::raw::stream::error>(test));
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
