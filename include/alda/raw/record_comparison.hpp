//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_COMPARISON_HPP_INCLUDED
#define ALDA_RAW_RECORD_COMPARISON_HPP_INCLUDED

#include <alda/raw/record_impl.hpp>
#include <fcppt/record/comparison.hpp>


namespace alda
{
namespace raw
{

template<
	typename Types
>
inline
bool
operator==(
	alda::raw::record<
		Types
	> const &_a,
	alda::raw::record<
		Types
	> const &_b
)
{
	return
		_a.get_base()
		==
		_b.get_base();
}

template<
	typename Types
>
inline
bool
operator!=(
	alda::raw::record<
		Types
	> const &_a,
	alda::raw::record<
		Types
	> const &_b
)
{
	return
		!(_a == _b);
}

}
}

#endif
