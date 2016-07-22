//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/src/log_parameters.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/default_level_streams.hpp>
#include <fcppt/log/name_fwd.hpp>
#include <fcppt/log/parameters.hpp>
#include <fcppt/log/format/optional_function.hpp>


fcppt::log::parameters
alda::log_parameters(
	fcppt::log::name const &_name
)
{
	return
		fcppt::log::parameters{
			_name,
			fcppt::log::default_level_streams(
				fcppt::io::clog()
			),
			fcppt::log::format::optional_function()
		};
}
