//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_STATIC_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_STATIC_DECL_HPP_INCLUDED

#include <alda/bindings/static_fwd.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct static_
{
	typedef
	Type
	element_type;
};

}
}

#endif
