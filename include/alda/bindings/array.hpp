//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_BINDINGS_ARRAY_HPP_INCLUDED
#define ALDA_BINDINGS_ARRAY_HPP_INCLUDED

#include <alda/bindings/array_decl.hpp> // IWYU pragma: export
#include <alda/raw/combine_static_sizes.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/fail.hpp>
#include <alda/raw/stream/get_error.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/array/size.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/mul.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace alda::bindings
{

template <typename Type, typename Adapted>
void place(
    alda::raw::dispatch_type<alda::bindings::array<Type, Adapted>>,
    alda::raw::element_type<alda::bindings::array<Type, Adapted>> const &_value,
    alda::raw::pointer _mem)
{
  for (auto const &elem : _value)
  {
    _mem = alda::raw::place_and_update<Adapted>(elem, _mem);
  }
}

template <typename Stream, typename Type, typename Adapted>
alda::raw::stream::result<Stream, alda::bindings::array<Type, Adapted>> make_generic(
    alda::raw::dispatch_type<alda::bindings::array<Type, Adapted>>,
    alda::raw::dispatch_type<Stream>,
    alda::raw::stream::reference<Stream> _stream)
{
  alda::raw::element_type<alda::bindings::array<Type, Adapted>> result{fcppt::no_init{}};

  for (auto const index : fcppt::make_int_range_count(fcppt::array::size<Type>::value))
  {
    fcppt::optional::object<alda::raw::stream::error> error{
        alda::raw::stream::get_error<Stream>(alda::raw::stream::bind<Stream>(
            alda::raw::make_generic<Stream, Adapted>(_stream),
            [&result, index](alda::raw::element_type<Adapted> &&_elem)
            {
              result.get_unsafe(index) = std::move(_elem);

              return alda::raw::stream::return_<Stream>(fcppt::unit{});
            }))};

    if (error.has_value())
    {
      return alda::raw::stream::fail<Stream, alda::bindings::array<Type, Adapted>>(
          std::move(error.get_unsafe().get()));
    }
  }

  return alda::raw::stream::return_<Stream>(std::move(result));
}

}

namespace alda::raw
{

template <typename Type, typename Adapted>
struct static_size_impl<alda::bindings::array<Type, Adapted>>
    : alda::raw::combine_static_sizes<
          fcppt::mpl::lambda<fcppt::mpl::mul>,
          fcppt::array::size<Type>,
          alda::raw::static_size<Adapted>>
{
};

}

#endif
