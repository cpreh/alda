//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/unsigned_decl.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/endianness/convert.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type
>
void
place(
	majutsu::dispatch_type<
		alda::bindings::unsigned_<
			Type
		>
	>,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		majutsu::fundamental<
			Type
		>
	>(
		fcppt::endianness::convert(
			_type,
			alda::endianness()
		),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::dispatch_type<
		alda::bindings::unsigned_<
			Type
		>
	>,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::endianness::convert(
			majutsu::make<
				majutsu::fundamental<
					Type
				>
			>(
				_beg
			),
			alda::endianness()
		);
}

}
}

namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct static_size<
	alda::bindings::unsigned_<
		Type
	>
>
:
majutsu::static_size<
	majutsu::fundamental<
		Type
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
