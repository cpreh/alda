//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_INSTANTIATE_DETAILS_HPP_INCLUDED
#define ALDA_SERIALIZATION_INSTANTIATE_DETAILS_HPP_INCLUDED

#include <alda/detail/export_external_class_instantiation.hpp>
#include <alda/serialization/detail/dispatch/base_impl.hpp>
#include <alda/serialization/detail/read/object_impl.hpp>


#define ALDA_SERIALIZATION_INSTANTIATE_DETAILS(\
	type_enum\
)\
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::detail::dispatch::base<\
	type_enum\
>;\
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::detail::read::object<\
	type_enum\
>

#endif
