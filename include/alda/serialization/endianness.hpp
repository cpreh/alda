//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_ENDIANNESS_HPP_INCLUDED
#define ALDA_SERIALIZATION_ENDIANNESS_HPP_INCLUDED

#include <fcppt/endianness/format.hpp>


namespace alda
{
namespace serialization
{

inline
constexpr
fcppt::endianness::format
endianness()
{
	return
		fcppt::endianness::format::little;
}

}
}

#endif
