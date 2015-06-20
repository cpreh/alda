//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DURATION_HPP_INCLUDED
#define ALDA_BINDINGS_DURATION_HPP_INCLUDED

#include <alda/bindings/duration_decl.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Adapted,
	typename Ratio
>
inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::duration<
			Adapted,
			Ratio
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::duration<
			Adapted,
			Ratio
		>
	> const &_duration,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		Adapted
	>(
		_duration.count(),
		_mem
	);
}

template<
	typename Adapted,
	typename Ratio
>
inline
majutsu::raw::element_type<
	alda::bindings::duration<
		Adapted,
		Ratio
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::duration<
			Adapted,
			Ratio
		>
	>,
	majutsu::raw::const_pointer const _mem
)
{
	return
		majutsu::raw::element_type<
			alda::bindings::duration<
				Adapted,
				Ratio
			>
		>(
			majutsu::raw::make<
				Adapted
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
	typename Adapted,
	typename Ratio
>
struct static_size<
	alda::bindings::duration<
		Adapted,
		Ratio
	>
>
:
majutsu::raw::static_size<
	Adapted
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
