//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_MAKE_OBJECT_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_MAKE_OBJECT_HPP_INCLUDED

#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read/element_impl.hpp>
#include <majutsu/init.hpp>


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
inline
Message
make_object(
	alda::serialization::istream &_stream
)
{
	return
		majutsu::init<
			Message
		>(
			alda::serialization::detail::read::element<
				Message
			>(
				_stream
			)
		);
}

}
}
}
}

#endif
