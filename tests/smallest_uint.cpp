//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/smallest_uint.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

int main()
{
  static_assert(std::is_same_v<
                alda::smallest_uint<
                    20U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                    >,
                std::uint8_t>);

  static_assert(std::is_same_v<
                alda::smallest_uint<
                    256U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                    >,
                std::uint16_t>);
}
