//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/call/detail/base_decl.hpp>
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/base_fwd.hpp>
#include <alda/message/concrete_decl.hpp>


template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
alda::call::detail::concrete<
	TypeEnum,
	Callee,
	Message
>::concrete()
:
	base_type()
{
}

template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
alda::call::detail::concrete<
	TypeEnum,
	Callee,
	Message
>::~concrete()
{
}

template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
typename Callee::result_type
alda::call::detail::concrete<
	TypeEnum,
	Callee,
	Message
>::call(
	Callee &_callee,
	message_type const &_message
) const
{
	return
		_callee(
			// TODO: static_cast
			dynamic_cast<
				alda::message::concrete<
					TypeEnum,
					Message
				> const &
			>(
				_message
			).value()
		);
}

#endif
