/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef ALDA_CALL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_CALL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/call/object_decl.hpp>
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/call/detail/make_instance.hpp>
#include <alda/message/base_decl.hpp>
#include <fcppt/mpl/for_each.hpp>


template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
alda::call::object<
	TypeEnum,
	Messages,
	Callee
>::object()
:
	instances_()
{
	fcppt::mpl::for_each<
		Messages
	>(
		alda::call::detail::make_instance<
			TypeEnum,
			Callee,
			instance_array
		>(
			instances_
		)
	);
}

template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
alda::call::object<
	TypeEnum,
	Messages,
	Callee
>::~object()
{
}

template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
typename alda::call::object<
	TypeEnum,
	Messages,
	Callee
>::result_type
alda::call::object<
	TypeEnum,
	Messages,
	Callee
>::operator()(
	message_base const &_message,
	Callee &_callee,
	default_callback const &_default_callback
) const
{
	typedef typename instance_array::size_type size_type;

	size_type const index(
		static_cast<
			size_type
		>(
			_message.type()
		)
	);

	return
		instances_.is_null(
			index
		)
		?
			_default_callback(
				_message
			)
		:
			instances_[
				index
			].call(
				_callee,
				_message
			);
}

#endif
