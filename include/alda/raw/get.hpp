//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_GET_HPP_INCLUDED
#define ALDA_RAW_GET_HPP_INCLUDED

#include <alda/raw/record_impl.hpp>
#include <fcppt/record/label_value_type.hpp>


namespace alda
{
namespace raw
{

template<
	typename Label,
	typename Types
>
fcppt::record::label_value_type<
	typename
	alda::raw::record<
		Types
	>::base,
	Label
>
get(
	alda::raw::record<
		Types
	> const &_arg
)
{
	return
		_arg. template get<
			Label
		>();
}

}
}

#endif
