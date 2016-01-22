//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_MAKE_ID_FWD_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_ID_FWD_HPP_INCLUDED

#include <alda/serialization/detail/message_int_type.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


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
std::integral_constant<
	alda::serialization::detail::message_int_type,
	fcppt::cast::enum_to_int<
		alda::serialization::detail::message_int_type
	>(
		MessageType
	)
>;

}
}

#endif
