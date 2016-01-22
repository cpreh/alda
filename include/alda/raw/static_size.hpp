//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STATIC_SIZE_HPP_INCLUDED
#define ALDA_RAW_STATIC_SIZE_HPP_INCLUDED

#include <alda/raw/detail/dynamic_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename T
>
struct static_size
:
alda::raw::detail::dynamic_size
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
