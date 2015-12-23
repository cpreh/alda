//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED

#include <alda/bindings/unsigned_decl.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/fundamental.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/endianness/convert.hpp>
#include <fcppt/endianness/format.hpp>
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
inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::unsigned_<
			Type,
			Endianness
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::unsigned_<
			Type,
			Endianness
		>
	> const &_type,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		majutsu::raw::fundamental<
			Type
		>
	>(
		fcppt::endianness::convert(
			_type,
			Endianness
		),
		_mem
	);
}

template<
	typename Type,
	fcppt::endianness::format Endianness
>
inline
majutsu::raw::element_type<
	alda::bindings::unsigned_<
		Type,
		Endianness
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::unsigned_<
			Type,
			Endianness
		>
	>,
	majutsu::raw::const_pointer const _beg
)
{
	return
		fcppt::endianness::convert(
			majutsu::raw::make<
				majutsu::raw::fundamental<
					Type
				>
			>(
				_beg
			),
			Endianness
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
	alda::bindings::unsigned_<
		Type,
		Endianness
	>
>
:
majutsu::raw::static_size<
	majutsu::raw::fundamental<
		Type
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
