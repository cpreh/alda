//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_BITFIELD_HPP_INCLUDED
#define ALDA_BINDINGS_BITFIELD_HPP_INCLUDED

#include <alda/bindings/array.hpp>
#include <alda/bindings/bitfield_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/endianness/format_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	fcppt::endianness::format Endianness
>
void
place(
	majutsu::dispatch_type<
		alda::bindings::bitfield<
			Type,
			Endianness
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::bitfield<
			Type,
			Endianness
		>
	> const &_value,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		typename
		alda::bindings::bitfield<
			Type,
			Endianness
		>::wrapped
	>(
		_value.array(),
		_mem
	);
}

template<
	typename Type,
	fcppt::endianness::format Endianness
>
majutsu::raw::element_type<
	alda::bindings::bitfield<
		Type,
		Endianness
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::bitfield<
			Type,
			Endianness
		>
	>,
	majutsu::raw::const_pointer const _mem
)
{
	return
		Type(
			majutsu::raw::make<
				typename
				alda::bindings::bitfield<
					Type,
					Endianness
				>::wrapped
			>(
				_mem
			)
		);
}

}
}

namespace majutsu
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type,
	fcppt::endianness::format Endianness
>
struct static_size<
	alda::bindings::bitfield<
		Type,
		Endianness
	>
>
:
majutsu::raw::static_size<
	typename
	alda::bindings::bitfield<
		Type,
		Endianness
	>::wrapped
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
