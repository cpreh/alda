//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_RECORD_IMPL_HPP_INCLUDED
#define ALDA_MESSAGE_RECORD_IMPL_HPP_INCLUDED

#include <alda/message/record_decl.hpp>
#include <alda/raw/record_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
>::record(
	base_type &&_base
)
:
	base_type(
		std::move(
			_base
		)
	)
{
}

template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
>::record(
	record &&
)
= default;

template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
>::record(
	record &_other
)
:
	base_type(
		static_cast<
			base_type &
		>(
			_other
		)
	)
{
}

template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
>::record(
	record const &
)
= default;

template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
> &
alda::message::record<
	Id,
	Types
>::operator=(
	record &&
)
= default;

template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
> &
alda::message::record<
	Id,
	Types
>::operator=(
	record const &
)
= default;

template<
	typename Id,
	typename Types
>
alda::message::record<
	Id,
	Types
>::~record()
{
}

template<
	typename Id,
	typename Types
>
typename
alda::message::record<
	Id,
	Types
>::base_type const &
alda::message::record<
	Id,
	Types
>::get_base() const
{
	return
		static_cast<
			base_type const &
		>(
			*this
		);
}

#endif
