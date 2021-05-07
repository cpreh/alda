//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_VARIANT_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_VARIANT_DECL_HPP_INCLUDED

#include <alda/bindings/unsigned_fwd.hpp>
#include <alda/bindings/variant_fwd.hpp>
#include <fcppt/variant/from_list_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <bit>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Types,
	typename AdaptedTypes
>
struct variant
{
	static_assert(
		metal::size<
			Types
		>::value
		==
		metal::size<
			AdaptedTypes
		>::value,
		"Types and AdaptedTypes must be of same size"
	);

	using
	element_type
	=
	fcppt::variant::from_list<
		Types
	>;

	using
	adapted_types
	=
	AdaptedTypes;

	using
	index_type
	=
	alda::bindings::unsigned_<
		std::uint8_t,
		std::endian::little
	>;
};

}
}

#endif
