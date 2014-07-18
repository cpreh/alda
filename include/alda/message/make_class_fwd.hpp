//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_MAKE_CLASS_FWD_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_CLASS_FWD_HPP_INCLUDED

#include <majutsu/class_fwd.hpp>
#include <majutsu/memory/raw_fwd.hpp>


namespace alda
{
namespace message
{

template<
	typename Message
>
using make_class
=
majutsu::class_<
	Message,
	majutsu::memory::raw
>;

}
}

#endif
