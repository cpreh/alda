//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_INSTANTIATE_CONTEXT_HPP_INCLUDED
#define ALDA_SERIALIZATION_INSTANTIATE_CONTEXT_HPP_INCLUDED

#include <alda/detail/export_external_class_instantiation.hpp>
#include <alda/serialization/impl/context_impl.hpp>


#define ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(\
	type_enum\
)\
template \
class \
ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
alda::serialization::context<\
	type_enum\
>

#endif
