//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_UNSIGNED_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_DECL_HPP_INCLUDED

#include <alda/bindings/fundamental_decl.hpp>
#include <alda/bindings/unsigned_fwd.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	fcppt::endianness::format Endianness
>
struct unsigned_
{
	typedef
	Type
	element_type;

	typedef
	alda::bindings::fundamental<
		Type
	>
	impl;

	static
	constexpr
	fcppt::endianness::format const endianness{
		Endianness
	};

	static_assert(
		std::is_unsigned<
			Type
		>::value,
		"alda::bindings::unsigned_ only works on unsigned types"
	);
};

}
}

#endif
