//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_FLOAT_HPP_INCLUDED
#define ALDA_BINDINGS_FLOAT_HPP_INCLUDED

#include <alda/bindings/float_decl.hpp>
#include <alda/bindings/float_type.hpp>
#include <alda/detail/symbol.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

ALDA_DETAIL_SYMBOL
majutsu::size_type
needed_size(
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &
);

ALDA_DETAIL_SYMBOL
void
place(
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &,
	majutsu::raw_pointer
);

ALDA_DETAIL_SYMBOL
alda::bindings::float_::type
make(
	alda::bindings::float_ const *,
	majutsu::const_raw_pointer
);

}
}

namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<>
struct static_size<
	alda::bindings::float_
>
:
majutsu::static_size<
	majutsu::fundamental<
		alda::bindings::float_type
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
