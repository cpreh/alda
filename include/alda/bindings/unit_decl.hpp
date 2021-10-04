//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_UNIT_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_UNIT_DECL_HPP_INCLUDED

#include <alda/bindings/unit_fwd.hpp>
#include <fcppt/unit_fwd.hpp>


namespace alda::bindings
{

struct unit
{
	using
	element_type
	=
	fcppt::unit;
};

}

#endif
