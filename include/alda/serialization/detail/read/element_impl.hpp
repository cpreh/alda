//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_ELEMENT_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_ELEMENT_IMPL_HPP_INCLUDED

#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read/element_decl.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <majutsu/access_role.hpp>
#include <majutsu/role.hpp>
#include <majutsu/role_value_type.hpp>


template<
	typename Message
>
alda::serialization::detail::read::element<
	Message
>::element(
	alda::serialization::istream &_stream
)
:
	stream_(
		_stream
	)
{
}

template<
	typename Message
>
template<
	typename Type,
	typename Tag
>
majutsu::role_value_type<
	Message,
	Tag
>
alda::serialization::detail::read::element<
	Message
>::operator()(
	majutsu::role<
		Type,
		Tag
	>
) const
{
	return
		alda::serialization::load<
			majutsu::access_role<
				majutsu::role<
					Type,
					Tag
				>
			>
		>::get(
			stream_
		);
}

#endif
