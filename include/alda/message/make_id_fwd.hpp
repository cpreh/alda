//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_MAKE_ID_FWD_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_ID_FWD_HPP_INCLUDED

#include <alda/message/id_binding_decl.hpp>
#include <alda/message/roles/type.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <majutsu/constant_fwd.hpp>
#include <majutsu/role_fwd.hpp>


namespace alda
{
namespace message
{

template<
	typename EnumType,
	typename EnumType::type MessageType
>
using make_id
=
majutsu::role<
	majutsu::constant<
		alda::message::id_binding,
		static_cast<
			alda::serialization::detail::message_int_type
		>(
			MessageType
		)
	>,
	alda::message::roles::type
>;

}
}

#endif
