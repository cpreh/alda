//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_STRONG_TYPEDEF_HPP_INCLUDED
#define ALDA_BINDINGS_STRONG_TYPEDEF_HPP_INCLUDED

#include <alda/bindings/strong_typedef_decl.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
void
place(
	alda::bindings::strong_typedef<
		Type,
		Adapted
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		Adapted
	>(
		_type.get(),
		_mem
	);
}

template<
	typename Type,
	typename Adapted
>
Type
make(
	alda::bindings::strong_typedef<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		Type(
			majutsu::make<
				Adapted
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
	typename Type,
	typename Adapted
>
struct static_size<
	alda::bindings::strong_typedef<
		Type,
		Adapted
	>
>
:
majutsu::static_size<
	Adapted
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
