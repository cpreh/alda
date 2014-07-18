//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_BITFIELD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_BITFIELD_DECL_HPP_INCLUDED

#include <alda/bindings/array_fwd.hpp>
#include <alda/bindings/bitfield_fwd.hpp>
#include <alda/bindings/unsigned_fwd.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type
>
struct bitfield
{
	typedef
	Type
	type;

	typedef
	alda::bindings::array<
		typename
		type::array_type,
		alda::bindings::unsigned_<
			typename
			type::internal_type
		>
	>
	wrapped;
};

}
}

#endif
