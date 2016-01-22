//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_ELEMENT_TYPE_TPL_HPP_INCLUDED
#define ALDA_RAW_ELEMENT_TYPE_TPL_HPP_INCLUDED


namespace alda
{
namespace raw
{

template<
	typename Element
>
struct element_type_tpl
{
	typedef
	typename
	Element::element_type
	type;
};

}
}

#endif
