//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_FUNDAMENTAL_HPP_INCLUDED
#define ALDA_BINDINGS_FUNDAMENTAL_HPP_INCLUDED

#include <alda/bindings/fundamental_decl.hpp>
#include <alda/bindings/signed.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/raw/fundamental.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace majutsu
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct static_size<
	alda::bindings::fundamental<
		Type
	>
>
:
majutsu::raw::static_size<
	majutsu::raw::fundamental<
		Type
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
