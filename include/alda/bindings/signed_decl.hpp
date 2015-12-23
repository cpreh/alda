//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_SIGNED_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_SIGNED_DECL_HPP_INCLUDED

#include <alda/bindings/signed_fwd.hpp>
#include <majutsu/raw/fundamental_decl.hpp>
#include <fcppt/endianness/format_fwd.hpp>
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
	typename Type,
	fcppt::endianness::format
>
struct signed_
:
majutsu::raw::fundamental<
	Type
>
{
	static_assert(
		std::is_signed<
			Type
		>::value,
		"alda::bindings::signed_ only works on signed types"
	);
};

FCPPT_PP_POP_WARNING

}
}

#endif
