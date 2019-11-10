//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_DETAIL_TO_NUMBER_HPP_INCLUDED
#define ALDA_RAW_DETAIL_TO_NUMBER_HPP_INCLUDED

#include <alda/raw/detail/convert_number.hpp>
#include <fcppt/metal/to_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/lambda.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace detail
{

template<
	typename Type
>
using
to_number
=
alda::raw::detail::convert_number<
	Type,
	metal::lambda<
		fcppt::metal::to_number
	>
>;

}
}
}

#endif
