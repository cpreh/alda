//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_FUNDAMENTAL_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_FUNDAMENTAL_DECL_HPP_INCLUDED

#include <alda/bindings/fundamental_fwd.hpp>
#include <alda/bindings/signed_decl.hpp>
#include <alda/bindings/unsigned_decl.hpp>
#include <fcppt/endianness/format_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
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
	fcppt::endianness::format Endianness
>
struct fundamental
:
boost::mpl::if_<
	std::is_signed<
		Type
	>,
	alda::bindings::signed_<
		Type,
		Endianness
	>,
	alda::bindings::unsigned_<
		Type,
		Endianness
	>
>::type
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
