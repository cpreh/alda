//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED

#include <alda/bindings/record_fwd.hpp>
#include <alda/bindings/unsigned_fwd.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

// TODO: Make a special version for staticically sized records
template<
	typename Type
>
struct record
{
	typedef
	Type
	element_type;

	// TODO: What should we use here?
	typedef
	alda::bindings::unsigned_<
		std::uint16_t,
		fcppt::endianness::format::little
	>
	length_type;
};

}
}

#endif