//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ENUM_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_HPP_INCLUDED

#include <alda/bindings/enum_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/cast_to_enum.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Enum,
	typename Underlying
>
inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::enum_<
			Enum,
			Underlying
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::enum_<
			Enum,
			Underlying
		>
	> const &_enum,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		alda::bindings::unsigned_<
			Underlying
		>
	>(
		fcppt::cast::enum_to_int<
			Underlying
		>(
			_enum
		),
		_mem
	);
}

template<
	typename Enum,
	typename Underlying
>
inline
majutsu::raw::element_type<
	alda::bindings::enum_<
		Enum,
		Underlying
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::enum_<
			Enum,
			Underlying
		>
	>,
	majutsu::raw::const_pointer const _beg
)
{
	return
		fcppt::cast_to_enum<
			Enum
		>(
			majutsu::raw::make<
				alda::bindings::unsigned_<
					Underlying
				>
			>(
				_beg
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
	typename Enum,
	typename Underlying
>
struct static_size<
	alda::bindings::enum_<
		Enum,
		Underlying
	>
>
:
majutsu::raw::static_size<
	alda::bindings::unsigned_<
		Underlying
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
