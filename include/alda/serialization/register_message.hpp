//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_REGISTER_MESSAGE_HPP_INCLUDED
#define ALDA_SERIALIZATION_REGISTER_MESSAGE_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/register_impl.hpp> // IWYU pragma: keep

#define ALDA_SERIALIZATION_REGISTER_MESSAGE(context, type_enum, message_type) \
\
  alda::serialization::detail::dispatch::register_<type_enum, message_type> const \
  register_class_tmp(context)

#endif
