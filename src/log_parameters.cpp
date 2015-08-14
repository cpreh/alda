//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/log_context.hpp>
#include <alda/src/log_parameters.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters.hpp>


fcppt::log::parameters
alda::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters(
			fcppt::io::clog(),
			fcppt::log::level::info
		)
		.context_location(
			alda::log_context(),
			_location
		)
		.enabled(
			true
		);
}
