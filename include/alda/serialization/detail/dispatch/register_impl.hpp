//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_IMPL_HPP_INCLUDED

#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/detail/dispatch/base_fwd.hpp>
#include <alda/serialization/detail/dispatch/concrete_decl.hpp>
#include <alda/serialization/detail/dispatch/register_decl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <exception>
#include <memory>
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
	typedef std::unique_ptr<
		alda::serialization::detail::dispatch::base<
			TypeEnum
		>
	> dispatcher_base_unique_ptr;

	typedef typename boost::mpl::at_c<
		typename Message::memory_type::types,
		0
	>::type msg_type;

	// TODO: fix this cast here, maybe replace majutsu::constant by an enum wrapper
	if(
		!fcppt::container::ptr::insert_unique_ptr_map(
			_context.handlers_,
			static_cast<
				typename TypeEnum::type
			>(
				msg_type::value
			),
			dispatcher_base_unique_ptr(
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
			<< static_cast<
				unsigned
			>(
				msg_type::value
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
