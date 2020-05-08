//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/serialization/detail/read_decl.hpp>
#include <alda/serialization/detail/dispatch/concrete_decl.hpp>
#include <fcppt/tag.hpp>


template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::concrete()
= default;

template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::~concrete()
= default;

template<
	typename TypeEnum,
	typename Message
>
typename alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::message_unique_ptr
alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::on_dispatch(
	reader const &_reader
) const
{
	return
		_reader(
			fcppt::tag<
				Message
			>()
		);
}

#endif
