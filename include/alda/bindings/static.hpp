//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_STATIC_HPP_INCLUDED
#define ALDA_BINDINGS_STATIC_HPP_INCLUDED

#include <alda/bindings/array.hpp>
#include <alda/bindings/static_decl.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/make.hpp>
#include <majutsu/needed_size.hpp>
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
	majutsu::dispatch_type<
		alda::bindings::static_<
			Type,
			Adapted
		>
	>,
	Type const &_value,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		alda::bindings::array<
			typename
			Type::storage_type,
			Adapted
		>
	>(
		_value.storage(),
		_mem
	);
}

template<
	typename Type,
	typename Adapted
>
Type
make(
	majutsu::dispatch_type<
		alda::bindings::static_<
			Type,
			Adapted
		>
	>,
	majutsu::const_raw_pointer const _mem
)
{
	return
		Type(
			majutsu::make<
				alda::bindings::array<
					typename
					Type::storage_type,
					Adapted
				>
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
	typename Type,
	typename Adapted
>
struct static_size<
	alda::bindings::static_<
		Type,
		Adapted
	>
>
:
majutsu::static_size<
	alda::bindings::array<
		typename
		Type::storage_type,
		Adapted
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
