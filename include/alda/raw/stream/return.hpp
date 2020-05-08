//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STREAM_RETURN_HPP_INCLUDED
#define ALDA_RAW_STREAM_RETURN_HPP_INCLUDED

#include <alda/raw/stream/error.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
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
std::enable_if_t<
	!Stream::can_fail,
	Type
>
return_(
	Type &&_value
)
{
	return
		std::forward<
			Type
		>(
			_value
		);
}

template<
	typename Stream,
	typename Type
>
inline
std::enable_if_t<
	Stream::can_fail,
	fcppt::either::object<
		alda::raw::stream::error,
		fcppt::type_traits::remove_cv_ref_t<
			Type
		>
	>
>
return_(
	Type &&_value
)
{
	return
		fcppt::either::object<
			alda::raw::stream::error,
			fcppt::type_traits::remove_cv_ref_t<
				Type
			>
		>(
			std::forward<
				Type
			>(
				_value
			)
		);
}

}
}
}

#endif
