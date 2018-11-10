//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DECLARE_MESSAGE_HPP_INCLUDED
#define ALDA_SERIALIZATION_DECLARE_MESSAGE_HPP_INCLUDED

#include <alda/detail/export_external_class_instantiation.hpp>
#include <alda/detail/export_external_function_instantiation.hpp>
#include <alda/serialization/detail/read_decl.hpp>
#include <alda/serialization/detail/dispatch/concrete_decl.hpp>
#include <alda/serialization/detail/dispatch/register_decl.hpp>
#include <fcppt/tag.hpp>


#define ALDA_SERIALIZATION_DECLARE_MESSAGE(\
	type_enum,\
	message_type\
)\
extern \
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::detail::dispatch::concrete<\
	type_enum,\
	message_type\
>; \
\
extern \
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::detail::dispatch::register_<\
	type_enum,\
	message_type\
>; \
\
extern \
template \
ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION \
alda::serialization::detail::read<\
	type_enum\
>::message_unique_ptr \
alda::serialization::detail::read<\
	type_enum\
>::operator()(\
	fcppt::tag<\
		message_type \
	> \
) const

#endif
