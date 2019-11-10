//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED
#define ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED

#include <alda/call/detail/base_impl.hpp>
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/detail/extract_id.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/lambda/trait.hpp>
#include <metal/list/any_of.hpp>
#include <metal/list/at.hpp>
#include <metal/list/find_if.hpp>
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
	metal::any_of<
		Messages,
		metal::bind<
			metal::trait<
				std::is_same
			>,
			metal::always<
				Type
			>,
			metal::lambda<
				alda::message::detail::extract_id
			>
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
							metal::at<
								Messages,
								metal::find_if<
									Messages,
									metal::bind<
										metal::trait<
											std::is_same
										>,
										metal::always<
											Type
										>,
										metal::lambda<
											alda::message::detail::extract_id
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
