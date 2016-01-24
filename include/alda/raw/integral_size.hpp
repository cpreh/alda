//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_INTEGRAL_SIZE_HPP_INCLUDED
#define ALDA_RAW_INTEGRAL_SIZE_HPP_INCLUDED

#include <alda/raw/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

template<
	alda::raw::size_type Size
>
using integral_size
=
boost::mpl::integral_c<
	alda::raw::size_type,
	Size
>;

}
}

#endif