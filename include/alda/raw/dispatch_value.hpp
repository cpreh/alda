//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_DISPATCH_VALUE_HPP_INCLUDED
#define ALDA_RAW_DISPATCH_VALUE_HPP_INCLUDED

#include <alda/raw/dispatch_type.hpp>


namespace alda
{
namespace raw
{

template<
	typename Type
>
inline
alda::raw::dispatch_type<
	Type
>
dispatch_value()
{
	return
		nullptr;
}

}
}

#endif
