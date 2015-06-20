//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_OPTIONAL_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_OPTIONAL_DECL_HPP_INCLUDED

#include <alda/bindings/bool_fwd.hpp>
#include <alda/bindings/optional_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct optional
{
	typedef
	fcppt::optional<
		Type
	>
	element_type;

	typedef
	alda::bindings::bool_
	bool_type;
};

}
}

#endif
