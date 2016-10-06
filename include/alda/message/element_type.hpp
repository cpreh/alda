//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_ELEMENT_TYPE_HPP_INCLUDED
#define ALDA_MESSAGE_ELEMENT_TYPE_HPP_INCLUDED


namespace alda
{
namespace message
{

template<
	typename Object
>
using
element_type
=
typename
Object::element_type;

}
}

#endif
