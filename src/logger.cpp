//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/log_location.hpp>
#include <alda/logger.hpp>
#include <alda/src/log_parameters.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	alda::logger,
	alda::log_parameters(
		alda::log_location()
	)
)
