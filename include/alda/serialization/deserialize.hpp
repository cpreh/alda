//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/endianness.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <alda/serialization/detail/dispatch/map.hpp>
#include <alda/serialization/detail/read/object_decl.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/cast/promote.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/io/read_exn.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
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
		==
		1u,
		"Only message types of size 1 are currently supported, sorry"
	);

	auto const type(
		fcppt::io::read_exn<
			alda::serialization::detail::message_int_type
		>(
			_stream,
			alda::serialization::endianness()
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
			FCPPT_TEXT("Invalid message ")
			+
			fcppt::insert_to_fcppt_string(
				fcppt::cast::promote(
					type
				)
			)
			+
			FCPPT_TEXT(" received!")
		);

	message_type const casted_type(
		static_cast<
			message_type
		>(
			type
		)
	);

	typedef
	alda::serialization::detail::read::object<
		TypeEnum
	>
	reader;

	reader cur_reader(
		_stream
	);

	return
		fcppt::optional::to_exception(
			fcppt::container::find_opt_mapped(
				_context.handlers(),
				casted_type
			),
			[]{
				return
					alda::exception(
						FCPPT_TEXT("No handler for a message found.")
					);
			}
		)->on_dispatch(
			cur_reader
		);
}

}
}

#endif
