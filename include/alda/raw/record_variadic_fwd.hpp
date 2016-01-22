//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_VARIADIC_FWD_HPP_INCLUDED
#define ALDA_RAW_RECORD_VARIADIC_FWD_HPP_INCLUDED

#include <alda/raw/record_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

template<
	typename... Types
>
using
record_variadic
=
alda::raw::record<
	boost::mpl::vector<
		Types...
	>
>;

}
}

#endif
