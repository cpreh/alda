//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/is_static_size_v.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <bit>
#include <cstdint>
#include <sstream>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{

constexpr std::endian const endianness{std::endian::little};

using length_binding = alda::bindings::unsigned_<std::uint16_t, endianness>;

using uint_binding = alda::bindings::fundamental<unsigned>;

using uint_vector = std::vector<unsigned>;

using dynamic_len_binding = alda::bindings::dynamic_len<uint_vector, uint_binding, length_binding>;

static_assert(!alda::raw::is_static_size_v<alda::raw::static_size<dynamic_len_binding>>);

using either_result_type = fcppt::either::object<alda::raw::stream::error, uint_vector>;

}

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bindings::dynamic_len", "[alda]")
{
  uint_vector const vec{1, 2};

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<dynamic_len_binding>(stream, vec);

  either_result_type const result(
      alda::raw::make_generic<alda::raw::stream::istream, dynamic_len_binding>(stream));

  CHECK(result == either_result_type{vec});
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
