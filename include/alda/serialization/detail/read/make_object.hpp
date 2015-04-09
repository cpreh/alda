//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_MAKE_OBJECT_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_MAKE_OBJECT_HPP_INCLUDED

#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read/element_impl.hpp>
#include <majutsu/is_role.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace read
{

template<
	typename Message
>
Message
make_object(
	alda::serialization::istream &_stream
)
{
	Message obj{
		fcppt::no_init()
	};

	boost::mpl::for_each<
		boost::mpl::filter_view<
			typename Message::memory_type::types,
			majutsu::is_role<
				boost::mpl::_1
			>
		>
	>(
		alda::serialization::detail::read::element<
			Message
		>(
			_stream,
			obj
		)
	);

	return
		std::move(
			obj
		);
}

}
}
}
}

#endif
