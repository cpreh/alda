//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ENUM_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_DECL_HPP_INCLUDED

#include <alda/bindings/enum_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Enum,
	typename Underlying
>
struct enum_
{
	typedef Enum type;

	static_assert(
		std::is_enum<
			Enum
		>::value,
		"Enum ist not an enumeration type"
	);
};

}
}

#endif
