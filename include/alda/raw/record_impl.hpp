//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_IMPL_HPP_INCLUDED
#define ALDA_RAW_RECORD_IMPL_HPP_INCLUDED

#include <alda/raw/record_decl.hpp>
#include <majutsu/record_impl.hpp>


template<
	typename Types
>
alda::raw::record<
	Types
>::record(
	record &&
)
= default;

template<
	typename Types
>
alda::raw::record<
	Types
>::record(
	record &_other
)
:
	base(
		static_cast<
			base &
		>(
			_other
		)
	)
{
}

template<
	typename Types
>
alda::raw::record<
	Types
>::record(
	record const &
)
= default;

template<
	typename Types
>
alda::raw::record<
	Types
> &
alda::raw::record<
	Types
>::operator=(
	record &&
)
= default;

template<
	typename Types
>
alda::raw::record<
	Types
> &
alda::raw::record<
	Types
>::operator=(
	record const &
)
= default;

template<
	typename Types
>
alda::raw::record<
	Types
>::~record()
{
}

template<
	typename Types
>
typename
alda::raw::record<
	Types
>::base const &
alda::raw::record<
	Types
>::get_base() const
{
	return
		*this;
}

#endif
