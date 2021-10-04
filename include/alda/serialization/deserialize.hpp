//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/message_type.hpp>
#include <alda/serialization/detail/read_decl.hpp>
#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/optional/to_exception.hpp>


namespace alda::serialization
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
	alda::serialization::detail::read<
		TypeEnum
	> cur_reader(
		_stream
	);

	return
		fcppt::optional::to_exception(
			fcppt::container::find_opt_mapped(
				_context.handlers(),
				fcppt::either::to_exception(
					alda::raw::make_generic<
						alda::raw::stream::istream,
						alda::serialization::detail::message_type<
							TypeEnum
						>
					>(
						_stream
					),
					[](
						alda::raw::stream::error const &_message
					){
						return
							alda::exception{
								FCPPT_TEXT("Invalid message type: ")
								+
								_message.get()
							};
					}
				)
			),
			[]{
				return
					alda::exception(
						FCPPT_TEXT("No handler for a message found.")
					);
			}
		).get()->on_dispatch(
			cur_reader
		);
}

}

#endif
