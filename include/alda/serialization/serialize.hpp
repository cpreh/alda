//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/serialization/ostream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
void
serialize(
	alda::serialization::ostream &_stream,
	alda::message::base<
		TypeEnum
	> const &_message
)
{
	_stream.write(
		reinterpret_cast<
			alda::serialization::ostream::char_type const *
		>(
			_message.data()
		),
		static_cast<
			std::streamsize
		>(
			_message.size()
		)
	);
}

}
}

#endif
