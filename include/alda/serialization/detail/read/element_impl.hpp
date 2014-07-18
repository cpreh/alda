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


template<
	typename Class
>
alda::serialization::detail::read::element<
	Class
>::element(
	alda::serialization::istream &_stream,
	Class &_object
)
:
	stream_(
		_stream
	),
	object_(
		_object
	)
{
}

template<
	typename Class
>
template<
	typename Role
>
void
alda::serialization::detail::read::element<
	Class
>::operator()(
	Role const &
) const
{
	object_. template set<
		typename Role::tag
	>(
		alda::serialization::load<
			typename majutsu::access_role<
				Role
			>::type
		>::get(
			stream_
		)
	);
}

#endif
