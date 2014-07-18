//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <alda/serialization/detail/dispatch/map.hpp>
#include <alda/serialization/detail/read/object_decl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
alda::message::base_unique_ptr<
	TypeEnum
>
deserialize(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::serialization::istream &_stream
)
{
	typedef typename TypeEnum::type message_type;

	// TODO: we can't specify the endianness of the message type at the moment
	static_assert(
		sizeof(
			alda::serialization::detail::message_int_type
		)
		== 1u,
		"Only message types of size 1 are currently supported, sorry"
	);

	alda::serialization::detail::message_int_type type;

	// TODO: fix endianness here
	_stream.read(
		reinterpret_cast<
			char *
		>(
			&type
		),
		static_cast<
			std::streamsize
		>(
			sizeof(
				alda::serialization::detail::message_int_type
			)
		)
	);

	FCPPT_ASSERT_THROW(
		static_cast<
			std::size_t
		>(
			_stream.gcount()
		)
		==
		sizeof(
			alda::serialization::detail::message_int_type
		),
		alda::exception
	);

	_stream.unget();

	if(
		type
		>=
		static_cast<
			alda::serialization::detail::message_int_type
		>(
			TypeEnum::size::value
		)
	)
		throw alda::exception(
			FCPPT_TEXT("Invalid message received!")
		);

	message_type const casted_type(
		static_cast<
			message_type
		>(
			type
		)
	);

	typedef alda::serialization::detail::dispatch::map<
		TypeEnum
	> dispatch_map;

	typename dispatch_map::const_iterator const it(
		_context.handlers().find(
			casted_type
		)
	);

	if(
		it == _context.handlers().end()
	)
		throw alda::exception(
			FCPPT_TEXT("No handler for a message found.")
		);

	typedef alda::serialization::detail::read::object<
		TypeEnum
	> reader;

	reader cur_reader(
		_stream
	);

	return
		it->second->on_dispatch(
			cur_reader
		);
}

}
}

#endif
