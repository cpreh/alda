//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_BOOL_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_BOOL_DECL_HPP_INCLUDED

#include <alda/bindings/bool_fwd.hpp>
#include <alda/bindings/unsigned_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace alda::bindings
{

struct bool_
{
	using
	element_type
	=
	bool;

	using
	wrapped_type
	=
	alda::bindings::unsigned_<
		std::uint8_t,
		std::endian::little
	>;
};

}

#endif
