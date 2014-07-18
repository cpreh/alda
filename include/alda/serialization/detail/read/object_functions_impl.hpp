//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_OBJECT_FUNCTIONS_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_OBJECT_FUNCTIONS_IMPL_HPP_INCLUDED

#include <alda/message/make_concrete_ptr.hpp>
#include <alda/serialization/detail/read/make_object.hpp>
#include <alda/serialization/detail/read/object_decl.hpp>


template<
	typename TypeEnum
>
template<
	typename Message
>
typename alda::serialization::detail::read::object<
	TypeEnum
>::message_unique_ptr
alda::serialization::detail::read::object<
	TypeEnum
>::operator()() const
{
	return
		alda::message::make_concrete_ptr<
			TypeEnum
		>(
			alda::serialization::detail::read::make_object<
				Message
			>(
				stream_
			)
		);
}

#endif
