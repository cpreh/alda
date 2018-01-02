//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED
#define ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED

#include <alda/call/detail/base_impl.hpp>
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/detail/extract_id_tpl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/functions/logical/not.hpp>
#include <brigand/sequences/contains.hpp>
#include <brigand/sequences/front.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types/args.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace call
{
namespace detail
{

template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
struct make_instance
{
	typedef
	alda::call::detail::base<
		TypeEnum,
		Callee
	>
	base;

	typedef
	fcppt::optional::object<
		fcppt::unique_ptr<
			base
		>
	>
	optional_base_unique_ptr;

	template<
		typename Type
	>
	using
	has_message
	=
	brigand::not_<
		std::is_same<
			brigand::find<
				Messages,
				brigand::bind<
					std::is_same,
					brigand::pin<
						Type
					>,
					alda::message::detail::extract_id_tpl<
						brigand::_1
					>
				>
			>,
			brigand::list<>
		>
	>;

	template<
		typename Type
	>
	typename
	std::enable_if<
		has_message<
			Type
		>::value,
		optional_base_unique_ptr
	>::type
	operator()(
		Type
	) const
	{
		return
			optional_base_unique_ptr{
				fcppt::unique_ptr_to_base<
					base
				>(
					fcppt::make_unique_ptr<
						alda::call::detail::concrete<
							TypeEnum,
							Callee,
							brigand::front<
								brigand::find<
									Messages,
									brigand::bind<
										std::is_same,
										brigand::pin<
											Type
										>,
										alda::message::detail::extract_id_tpl<
											brigand::_1
										>
									>
								>
							>
						>
					>()
				)
			};
	}

	template<
		typename Type
	>
	typename
	std::enable_if<
		!has_message<
			Type
		>::value,
		optional_base_unique_ptr
	>::type
	operator()(
		Type
	) const
	{
		return
			optional_base_unique_ptr();
	}
};

}
}
}

#endif
