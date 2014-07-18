//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_TYPE_ENUM_FCPPT_FWD_HPP_INCLUDED
#define ALDA_TYPE_ENUM_FCPPT_FWD_HPP_INCLUDED

#include <alda/type_enum_fwd.hpp>
#include <fcppt/enum_size.hpp>


namespace alda
{

template<
	typename Enum
>
using type_enum_fcppt
=
alda::type_enum<
	Enum,
	typename
	fcppt::enum_size<
		Enum
	>::type
>;

}

#endif
