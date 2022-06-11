//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/bindings/array.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/array/object.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <bit>
#include <sstream>
#include <fcppt/config/external_end.hpp>

namespace
{

using int_array2 = fcppt::array::object<unsigned, 2>;

using array_binding = alda::bindings::
    array<int_array2, alda::bindings::unsigned_<int_array2::value_type, std::endian::little>>;

static_assert(alda::raw::static_size<array_binding>::value == sizeof(unsigned) * 2U);

using either_result_type = fcppt::either::object<alda::raw::stream::error, int_array2>;

}

FCPPT_CATCH_BEGIN

TEST_CASE("bindings::array", "[alda]")
{
  int_array2 const test{2U, 4U};

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<array_binding>(stream, test);

  CHECK(
      alda::serialization::read<array_binding>(stream) ==
      fcppt::either::make_success<alda::raw::stream::error>(test));
}

FCPPT_CATCH_END
