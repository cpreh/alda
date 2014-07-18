//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
