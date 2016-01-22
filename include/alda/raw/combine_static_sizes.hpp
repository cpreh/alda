//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED
#define ALDA_RAW_COMBINE_STATIC_SIZES_HPP_INCLUDED

#include <alda/raw/detail/dynamic_size.hpp>
#include <alda/raw/detail/is_static_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Size1,
	typename Size2
>
struct combine_static_sizes
:
boost::mpl::eval_if<
	boost::mpl::and_<
		alda::raw::detail::is_static_size<
			Size1
		>,
		alda::raw::detail::is_static_size<
			Size2
		>
	>,
	boost::mpl::plus<
		Size1,
		Size2
	>,
	boost::mpl::identity<
		alda::raw::detail::dynamic_size
	>
>::type
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
