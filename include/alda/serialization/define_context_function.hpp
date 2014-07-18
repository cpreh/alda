//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION_HPP_INCLUDED
#define ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION_HPP_INCLUDED

#include <alda/serialization/context_decl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


#define ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(\
	type_enum,\
	function_name\
) \
FCPPT_PP_PUSH_WARNING \
FCPPT_PP_DISABLE_VC_WARNING(4640) \
alda::serialization::context<\
	type_enum\
> &\
function_name()\
{\
	static alda::serialization::context<\
		type_enum\
	> object;\
\
	return object;\
} \
FCPPT_PP_POP_WARNING

#endif
