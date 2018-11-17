//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_INSTANTIATE_CONCRETE_HPP_INCLUDED
#define ALDA_MESSAGE_INSTANTIATE_CONCRETE_HPP_INCLUDED

#include <alda/message/impl/concrete_impl.hpp>


#define ALDA_MESSAGE_INSTANTIATE_CONCRETE(\
	type_enum,\
	message_type\
)\
template \
class \
alda::message::concrete<\
	type_enum,\
	message_type\
>

#endif
