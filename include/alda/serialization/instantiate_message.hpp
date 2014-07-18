//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define ALDA_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <alda/detail/export_external_class_instantiation.hpp>
#include <alda/detail/export_external_function_instantiation.hpp>
#include <alda/serialization/detail/dispatch/concrete_impl.hpp>
#include <alda/serialization/detail/dispatch/register_impl.hpp>
#include <alda/serialization/detail/read/object_functions_impl.hpp>


#define ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(\
	type_enum,\
	message_type\
)\
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::detail::dispatch::concrete<\
	type_enum,\
	message_type\
>; \
\
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::detail::dispatch::register_<\
	type_enum,\
	message_type\
>; \
\
template \
ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION \
alda::serialization::detail::read::object<\
	type_enum\
>::message_unique_ptr \
alda::serialization::detail::read::object<\
	type_enum\
>::operator()<\
	message_type\
>() const

#endif
