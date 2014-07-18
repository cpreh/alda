//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ENUM_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_HPP_INCLUDED

#include <alda/bindings/enum_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/cast_to_enum.hpp>
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
void
place(
	alda::bindings::enum_<
		Enum,
		Underlying
	> const *,
	Enum const &_enum,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		alda::bindings::unsigned_<
			Underlying
		>
	>(
		static_cast<
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
Enum
make(
	alda::bindings::enum_<
		Enum,
		Underlying
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::cast_to_enum<
			Enum
		>(
			majutsu::make<
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
majutsu::static_size<
	alda::bindings::unsigned_<
		Underlying
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
