//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_OBJECT_FUNCTIONS_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_OBJECT_FUNCTIONS_IMPL_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/message/record_impl.hpp>
#include <alda/serialization/detail/read/object_decl.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/istream.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


template<
	typename TypeEnum
>
template<
	typename Message
>
typename
alda::serialization::detail::read::object<
	TypeEnum
>::message_unique_ptr
alda::serialization::detail::read::object<
	TypeEnum
>::operator()(
	fcppt::tag<
		Message
	>
) const
{
	return
		alda::message::make_concrete_ptr<
			TypeEnum
		>(
			Message{
				// TODO: Should we use raw memory here?
				fcppt::optional::to_exception(
					alda::raw::make_generic<
						alda::raw::stream::istream,
						typename
						Message::record::base_type
					>(
						stream_
					),
					[]{
						return
							alda::exception{
								FCPPT_TEXT("Message stream failed!")
							};
					}
				)
			}
		);
}

#endif
