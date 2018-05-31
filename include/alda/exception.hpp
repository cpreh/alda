//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_EXCEPTION_HPP_INCLUDED
#define ALDA_EXCEPTION_HPP_INCLUDED

#include <alda/exception_fwd.hpp>
#include <alda/detail/class_symbol.hpp>
#include <alda/detail/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>


namespace alda
{

class ALDA_DETAIL_CLASS_SYMBOL exception
:
	public fcppt::exception
{
public:
	ALDA_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::string &&
	);

	ALDA_DETAIL_SYMBOL
	explicit
	exception(
		fcppt::assert_::information const &
	);
};

}

#endif
