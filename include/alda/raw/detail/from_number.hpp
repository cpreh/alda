//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_DETAIL_FROM_NUMBER_HPP_INCLUDED
#define ALDA_RAW_DETAIL_FROM_NUMBER_HPP_INCLUDED

#include <alda/raw/detail/convert_number.hpp>
#include <fcppt/metal/from_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace detail
{

template<
	typename Dest,
	typename Type
>
using
from_number
=
alda::raw::detail::convert_number<
	Type,
	metal::bind<
		metal::lambda<
			fcppt::metal::from_number
		>,
		metal::always<
			Dest
		>,
		metal::always<
			Type
		>
	>
>;

}
}
}

#endif
