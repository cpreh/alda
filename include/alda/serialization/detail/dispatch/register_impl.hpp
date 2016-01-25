//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_IMPL_HPP_INCLUDED

#include <alda/message/detail/extract_id.hpp>
#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <alda/serialization/detail/dispatch/concrete_decl.hpp>
#include <alda/serialization/detail/dispatch/register_decl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/enum_to_underlying.hpp>
#include <fcppt/cast/promote.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::register_<
	TypeEnum,
	Message
>::register_(
	context &_context
)
{
	typedef
	alda::message::detail::extract_id<
		Message
	>
	constant_value;

	if(
		!_context.handlers_.emplace(
			constant_value::value,
			fcppt::unique_ptr_to_base<
				alda::serialization::detail::dispatch::base<
					TypeEnum
				>
			>(
				fcppt::make_unique_ptr<
					alda::serialization::detail::dispatch::concrete<
						TypeEnum,
						Message
					>
				>()
			)
		).second
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Message type registered twice: ")
			<<
			fcppt::cast::promote(
				fcppt::cast::enum_to_underlying(
					constant_value::value
				)
			)
			<< FCPPT_TEXT('\n');

		std::terminate();
	}
}

template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::register_<
	TypeEnum,
	Message
>::~register_()
{
}

#endif
