//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_ID_BINDING_FWD_HPP_INCLUDED
#define ALDA_MESSAGE_ID_BINDING_FWD_HPP_INCLUDED

#include <alda/bindings/fundamental_fwd.hpp>
#include <alda/serialization/endianness.hpp>
#include <alda/serialization/detail/message_int_type.hpp>


namespace alda
{
namespace message
{

typedef
alda::bindings::fundamental<
	alda::serialization::detail::message_int_type,
	alda::serialization::endianness()
>
id_binding;

}
}

#endif
