//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_FLOAT_HPP_INCLUDED
#define ALDA_BINDINGS_FLOAT_HPP_INCLUDED

#include <alda/bindings/float_decl.hpp>
#include <alda/bindings/float_type.hpp>
#include <alda/detail/symbol.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/fundamental.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <majutsu/raw/static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

ALDA_DETAIL_SYMBOL
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::float_
	>,
	majutsu::raw::element_type<
		alda::bindings::float_
	> const &
);

ALDA_DETAIL_SYMBOL
void
place(
	majutsu::dispatch_type<
		alda::bindings::float_
	>,
	majutsu::raw::element_type<
		alda::bindings::float_
	> const &,
	majutsu::raw::pointer
);

ALDA_DETAIL_SYMBOL
majutsu::raw::element_type<
	alda::bindings::float_
>
make(
	majutsu::dispatch_type<
		alda::bindings::float_
	>,
	majutsu::raw::const_pointer
);

}
}

namespace majutsu
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<>
struct static_size<
	alda::bindings::float_
>
:
majutsu::raw::static_size<
	majutsu::raw::fundamental<
		alda::bindings::float_type
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
