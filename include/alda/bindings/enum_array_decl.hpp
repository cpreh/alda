//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ENUM_ARRAY_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_ARRAY_DECL_HPP_INCLUDED

#include <alda/bindings/enum_array_fwd.hpp>


namespace alda::bindings
{

template<
	typename Type,
	typename Adapted
>
struct enum_array
{
	using
	element_type
	=
	Type;
};

}

#endif
