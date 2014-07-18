//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DURATION_HPP_INCLUDED
#define ALDA_BINDINGS_DURATION_HPP_INCLUDED

#include <alda/bindings/duration_decl.hpp>
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
	typename Adapted,
	typename Ratio
>
void
place(
	alda::bindings::duration<
		Adapted,
		Ratio
	> const *,
	typename
	alda::bindings::duration<
		Adapted,
		Ratio
	>::type const &_duration,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
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
typename
alda::bindings::duration<
	Adapted,
	Ratio
>::type
make(
	alda::bindings::duration<
		Adapted,
		Ratio
	> const *,
	majutsu::const_raw_pointer const _mem
)
{
	return
		typename
		alda::bindings::duration<
			Adapted,
			Ratio
		>::type(
			majutsu::make<
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
majutsu::static_size<
	Adapted
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
