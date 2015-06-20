//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ENUM_ARRAY_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_ARRAY_HPP_INCLUDED

#include <alda/bindings/array.hpp>
#include <alda/bindings/enum_array_decl.hpp>
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
	typename Type,
	typename Adapted
>
inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::enum_array<
			Type,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::enum_array<
			Type,
			Adapted
		>
	> const &_value,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		alda::bindings::array<
			typename
			Type::internal,
			Adapted
		>
	>(
		_value.impl(),
		_mem
	);
}

template<
	typename Type,
	typename Adapted
>
majutsu::raw::element_type<
	alda::bindings::enum_array<
		Type,
		Adapted
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::enum_array<
			Type,
			Adapted
		>
	>,
	majutsu::raw::const_pointer const _mem
)
{
	return
		Type{
			majutsu::raw::make<
				alda::bindings::array<
					typename
					Type::internal,
					Adapted
				>
			>(
				_mem
			)
		};
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
	typename Adapted
>
struct static_size<
	alda::bindings::enum_array<
		Type,
		Adapted
	>
>
:
majutsu::raw::static_size<
	alda::bindings::array<
		typename
		Type::internal,
		Adapted
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
