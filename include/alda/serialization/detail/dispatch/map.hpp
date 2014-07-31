//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_MAP_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_MAP_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace dispatch
{

template<
	typename TypeEnum
>
using map
=
std::map<
	typename TypeEnum::type,
	std::unique_ptr<
		alda::serialization::detail::dispatch::base<
			TypeEnum
		>
	>
>;

}
}
}
}

#endif
