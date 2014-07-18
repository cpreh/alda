//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_BOOL_HPP_INCLUDED
#define ALDA_BINDINGS_BOOL_HPP_INCLUDED

#include <alda/bindings/bool_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/static_size.hpp>
#include <majutsu/raw_pointer.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

inline
void
place(
	alda::bindings::bool_ const *,
	alda::bindings::bool_::type const _value,
	majutsu::raw_pointer const _data
)
{
	majutsu::place<
		alda::bindings::bool_::wrapped_type
	>(
		static_cast<
			alda::bindings::bool_::wrapped_type::type
		>(
			_value
		),
		_data
	);
}

inline
alda::bindings::bool_::type
make(
	alda::bindings::bool_ const *,
	majutsu::const_raw_pointer const _data
)
{
	return
		majutsu::make<
			alda::bindings::bool_::wrapped_type
		>(
			_data
		)
		!=
		fcppt::literal<
			alda::bindings::bool_::wrapped_type::type
		>(
			0
		);
}

}
}


namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<>
struct static_size<
	alda::bindings::bool_
>
:
majutsu::static_size<
	alda::bindings::bool_::wrapped_type
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
