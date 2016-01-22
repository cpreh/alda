//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_SIGNED_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_SIGNED_DECL_HPP_INCLUDED

#include <alda/bindings/signed_fwd.hpp>
#include <alda/bindings/unsigned_fwd.hpp>
#include <fcppt/endianness/format_fwd.hpp>
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
struct signed_
{
	typedef
	Type
	element_type;

	typedef
	alda::bindings::unsigned_<
		typename
		std::make_unsigned<
			Type
		>::type,
		Endianness
	>
	impl;

	static_assert(
		std::is_signed<
			Type
		>::value,
		"alda::bindings::signed_ only works on signed types"
	);
};

}
}

#endif
