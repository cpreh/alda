//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/exception.hpp>
#include <alda/bindings/signed.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <bit>
#include <cstdint>
#include <limits>
#include <sstream>
#include <fcppt/config/external_end.hpp>

namespace
{

using int_type = std::int16_t;

using int_binding = alda::bindings::signed_<int_type, std::endian::little>;

using either_result_type = fcppt::either::object<alda::raw::stream::error, int_type>;

void test_conversion(int_type const _value)
{
  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<int_binding>(stream, _value);

  either_result_type const result(
      alda::raw::make_generic<alda::raw::stream::istream, int_binding>(stream));

  CHECK(either_result_type{_value} == result);
}

}

FCPPT_CATCH_BEGIN

TEST_CASE("bindings::signed", "[alda]")
{
  int_type const max_value(std::numeric_limits<int_type>::max());

  int_type const min_value(std::numeric_limits<int_type>::min());

  test_conversion(fcppt::literal<int_type>(0));

  test_conversion(fcppt::literal<int_type>(
      1337 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  test_conversion(fcppt::literal<int_type>(
      -1337 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  test_conversion(max_value);

  test_conversion(fcppt::literal<int_type>(-max_value));

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_VC_WARNING(4127)
  if (min_value + max_value < 0)
  {
    // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
    std::ostringstream stream{};

    CHECK_THROWS_AS(alda::serialization::write<int_binding>(stream, min_value), alda::exception);
  }
  FCPPT_PP_POP_WARNING
}

FCPPT_CATCH_END
