//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_MAP_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_MAP_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
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
boost::ptr_map<
	typename TypeEnum::type,
	alda::serialization::detail::dispatch::base<
		TypeEnum
	>
>;

}
}
}
}

#endif
