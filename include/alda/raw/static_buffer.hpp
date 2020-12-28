//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STATIC_BUFFER_HPP_INCLUDED
#define ALDA_RAW_STATIC_BUFFER_HPP_INCLUDED

#include <alda/raw/data.hpp>
#include <alda/raw/static_size.hpp>
#include <fcppt/array/object_impl.hpp>


namespace alda
{
namespace raw
{

template<
	typename Type
>
using
static_buffer
=
fcppt::array::object<
	alda::raw::data,
	alda::raw::static_size<
		Type
	>::type::value
>;

}
}

#endif
