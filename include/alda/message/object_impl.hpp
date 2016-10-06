//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_MESSAGE_OBJECT_IMPL_HPP_INCLUDED

#include <alda/message/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Id,
	typename Type
>
alda::message::object<
	Id,
	Type
>::object(
	element_type const &_value
)
:
	value_(
		_value
	)
{
}

template<
	typename Id,
	typename Type
>
alda::message::object<
	Id,
	Type
>::object(
	element_type &&_value
)
:
	value_(
		std::move(
			_value
		)
	)
{
}

template<
	typename Id,
	typename Type
>
typename
alda::message::object<
	Id,
	Type
>::element_type const &
alda::message::object<
	Id,
	Type
>::get() const
{
	return
		value_;
}

#endif
