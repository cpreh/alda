//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STREAM_RETURN_HPP_INCLUDED
#define ALDA_RAW_STREAM_RETURN_HPP_INCLUDED

#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace stream
{

template<
	typename Stream,
	typename Type
>
inline
typename
std::enable_if<
	!Stream::can_fail,
	Type
>::type
return_(
	Type &&_value
)
{
	return
		std::move(
			_value
		);
}

template<
	typename Stream,
	typename Type
>
inline
typename
std::enable_if<
	Stream::can_fail,
	fcppt::optional::object<
		Type
	>
>::type
return_(
	Type &&_value
)
{
	return
		fcppt::optional::object<
			Type
		>(
			std::move(
				_value
			)
		);
}

}
}
}

#endif
