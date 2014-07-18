//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/exception.hpp>
#include <alda/bindings/invalid_variant.hpp>
#include <fcppt/text.hpp>


alda::bindings::invalid_variant::invalid_variant()
:
	alda::exception(
		FCPPT_TEXT("Invalid variant index")
	)
{
}
