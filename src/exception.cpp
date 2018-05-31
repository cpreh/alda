//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/information_fwd.hpp>
#include <fcppt/assert/make_message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


alda::exception::exception(
	fcppt::string &&_message
)
:
	fcppt::exception(
		std::move(
			_message
		)
	)
{
}

alda::exception::exception(
	fcppt::assert_::information const &_info
)
:
	fcppt::exception(
		fcppt::assert_::make_message(
			_info
		)
	)
{
}
