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
#include <fcppt/mpl/contains_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/utility/enable_if.hpp>
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

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename Type
	>
	struct has_message
	:
	fcppt::mpl::contains_if<
		Messages,
		std::is_same<
			Type,
			alda::message::detail::extract_id_tpl<
				boost::mpl::_1
			>
		>
	>
	{
	};

	FCPPT_PP_POP_WARNING

	template<
		typename Type
	>
	typename
	boost::enable_if<
		has_message<
			Type
		>,
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
							typename
							boost::mpl::deref<
								typename
								boost::mpl::find_if<
									Messages,
									std::is_same<
										Type,
										alda::message::detail::extract_id_tpl<
											boost::mpl::_1
										>
									>
								>::type
							>::type
						>
					>()
				)
			};
	}

	template<
		typename Type
	>
	typename
	boost::disable_if<
		has_message<
			Type
		>,
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
