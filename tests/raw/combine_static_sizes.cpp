#include <alda/bindings/fundamental.hpp>
#include <alda/raw/combine_static_sizes.hpp>
#include <alda/raw/is_static_size_v.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/detail/dynamic_size.hpp>
#include <fcppt/mpl/add.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

int main()
{
  static_assert(
      alda::raw::combine_static_sizes<
          fcppt::mpl::lambda<fcppt::mpl::add>,
          alda::raw::static_size<alda::bindings::fundamental<std::uint16_t>>,
          alda::raw::static_size<alda::bindings::fundamental<std::uint32_t>>>::value ==
      alda::raw::static_size<alda::bindings::fundamental<std::uint16_t>>::value +
          alda::raw::static_size<alda::bindings::fundamental<std::uint32_t>>::value);

  static_assert(!alda::raw::is_static_size_v<alda::raw::combine_static_sizes<
                    fcppt::mpl::lambda<fcppt::mpl::add>,
                    alda::raw::static_size<alda::bindings::fundamental<std::uint16_t>>,
                    alda::raw::static_size<void>>>);

  static_assert(std::is_same_v<
                alda::raw::combine_static_sizes<
                    fcppt::mpl::lambda<fcppt::mpl::add>,
                    alda::raw::detail::dynamic_size,
                    alda::raw::static_size<alda::bindings::fundamental<std::uint32_t>>>,
                alda::raw::detail::dynamic_size>);
}
