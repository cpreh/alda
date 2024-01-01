//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define ALDA_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <alda/serialization/detail/read_functions_impl.hpp> // IWYU pragma: keep
#include <alda/serialization/detail/dispatch/concrete_impl.hpp> // IWYU pragma: keep
#include <alda/serialization/detail/dispatch/register_impl.hpp> // IWYU pragma: keep
#include <fcppt/tag.hpp> // IWYU pragma: keep

#define ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(type_enum, message_type) \
  template class alda::serialization::detail::dispatch::concrete<type_enum, message_type>; \
\
  template class alda::serialization::detail::dispatch::register_<type_enum, message_type>; \
\
  template alda::serialization::detail::read<type_enum>::message_unique_ptr \
  alda::serialization::detail::read<type_enum>::operator()(fcppt::tag<message_type>) const

#endif
