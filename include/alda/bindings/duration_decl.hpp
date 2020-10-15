//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DURATION_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_DURATION_DECL_HPP_INCLUDED

#include <alda/bindings/duration_fwd.hpp>
#include <alda/raw/element_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Adapted,
	typename Ratio
>
struct duration
{
	using
	element_type
	=
	std::chrono::duration<
		alda::raw::element_type<
			Adapted
		>,
		Ratio
	>;
};

}
}

#endif
