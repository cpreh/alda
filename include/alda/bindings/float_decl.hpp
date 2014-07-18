//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_FLOAT_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_FLOAT_DECL_HPP_INCLUDED

#include <alda/bindings/float_fwd.hpp>
#include <alda/bindings/float_type.hpp>
#include <majutsu/fundamental_decl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

struct float_
:
majutsu::fundamental<
	alda::bindings::float_type
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
