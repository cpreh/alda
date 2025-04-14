//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_LENGTH_EXTRACT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_EXTRACT_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/error_output.hpp> // IWYU pragma: keep
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/length/remaining_size_function.hpp>
#include <alda/serialization/length/detail/binding.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace alda::serialization::length
{

template <typename LengthType>
fcppt::optional::object<LengthType> extract(
    alda::serialization::istream &_stream,
    alda::serialization::length::remaining_size_function const &_remaining_size)
{
  static_assert(std::is_unsigned_v<LengthType>);

  using return_type = fcppt::optional::object<LengthType>;

  return _remaining_size() <
                 fcppt::cast::size<std::streamsize>(fcppt::cast::to_signed(sizeof(LengthType)))
             ? return_type{}
             : return_type{fcppt::either::to_exception(
                   alda::raw::make_generic<
                       alda::raw::stream::istream,
                       alda::serialization::length::detail::binding<LengthType>>(_stream),
                   [](alda::raw::stream::error const &_error)
                   {
                     return alda::exception{
                         FCPPT_TEXT("Invalid remaining size in stream: ") +
                         fcppt::output_to_fcppt_string(_error)};
                   })};
}

}

#endif
