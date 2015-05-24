//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_DETAIL_EXTRACT_ID_HPP_INCLUDED
#define ALDA_MESSAGE_DETAIL_EXTRACT_ID_HPP_INCLUDED

#include <alda/message/roles/type.hpp>
#include <majutsu/extract_constant.hpp>


namespace alda
{
namespace message
{
namespace detail
{

template<
	typename Message
>
using extract_id
=
typename
majutsu::extract_constant<
	Message,
	alda::message::roles::type
>::type;

}
}
}

#endif
