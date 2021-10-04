//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_FUNDAMENTAL_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_FUNDAMENTAL_DECL_HPP_INCLUDED

#include <alda/bindings/fundamental_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda::bindings
{

template<
	typename Type
>
struct fundamental
{
	using
	element_type
	=
	Type;

	static_assert(
		std::is_fundamental_v<
			Type
		>,
		"T must be fundamental"
	);
};

}

#endif
