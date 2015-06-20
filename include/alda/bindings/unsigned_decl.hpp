//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_UNSIGNED_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_DECL_HPP_INCLUDED

#include <alda/bindings/unsigned_fwd.hpp>
#include <majutsu/raw/fundamental_decl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct unsigned_
:
majutsu::raw::fundamental<
	Type
>
{
	typedef
	majutsu::raw::fundamental<
		Type
	>
	impl;

	static_assert(
		std::is_unsigned<
			Type
		>::value,
		"alda::bindings::unsigned_ only works on unsigned types"
	);
};

FCPPT_PP_POP_WARNING

}
}

#endif
