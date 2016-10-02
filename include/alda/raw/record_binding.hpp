//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_BINDING_HPP_INCLUDED
#define ALDA_RAW_RECORD_BINDING_HPP_INCLUDED

#include <alda/raw/combine_static_sizes.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/record_impl.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/record/element_to_label.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/element_to_type_tpl.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Types
>
struct static_size<
	alda::raw::record<
		Types
	>
>
:
boost::mpl::fold<
	Types,
	alda::raw::integral_size<
		0
	>,
	alda::raw::combine_static_sizes<
		typename
		boost::mpl::lambda<
			boost::mpl::plus<
				boost::mpl::_,
				boost::mpl::_
			>
		>::type,
		alda::raw::static_size<
			fcppt::record::element_to_type_tpl<
				boost::mpl::_2
			>
		>,
		boost::mpl::_1
	>
>::type
{
};

FCPPT_PP_POP_WARNING

template<
	typename Types
>
alda::raw::size_type
needed_size(
	alda::raw::dispatch_type<
		alda::raw::record<
			Types
		>
	>,
	// TODO: why does gcc get confused here?
	//alda::raw::element_type<
	alda::raw::record<
		Types
	> const &_value
)
{
	return
		fcppt::algorithm::fold(
			Types{},
			fcppt::literal<
				alda::raw::size_type
			>(
				0
			),
			[
				&_value
			](
				auto const _tag,
				alda::raw::size_type const _size
			)
			{
				FCPPT_USE(
					_tag
				);

				typedef
				fcppt::tag_type<
					decltype(
						_tag
					)
				>
				role;

				return
					alda::raw::needed_size<
						fcppt::record::element_to_type<
							role
						>
					>(
						alda::raw::get<
							fcppt::record::element_to_label<
								role
							>
						>(
							_value
						)
					)
					+
					_size;
			}
		);
}

template<
	typename Types
>
inline
void
place(
	alda::raw::dispatch_type<
		alda::raw::record<
			Types
		>
	>,
	// TODO: why does gcc get confused here?
	//alda::raw::element_type<
	alda::raw::record<
		Types
	> const &_value,
	alda::raw::pointer _memory
)
{
	fcppt::algorithm::loop(
		Types{},
		[
			&_value,
			&_memory
		](
			auto const _tag
		)
		{
			FCPPT_USE(
				_tag
			);

			typedef
			fcppt::tag_type<
				decltype(
					_tag
				)
			>
			role;

			alda::raw::place_and_update<
				fcppt::record::element_to_type<
					role
				>
			>(
				alda::raw::get<
					fcppt::record::element_to_label<
						role
					>
				>(
					_value
				),
				_memory
			);
		}
	);
}

namespace detail
{

// TODO: Improve this by making std::tuple usable as a range
template<
	typename Types,
	typename Stream,
	typename Iterator,
	typename EndIterator,
	typename... Args
>
inline
typename
boost::enable_if<
	std::is_same<
		Iterator,
		EndIterator
	>,
	alda::raw::stream::result<
		Stream,
		alda::raw::record<
			Types
		>
	>
>::type
read(
	alda::raw::stream::reference<
		Stream
	>,
	Args &&..._args
)
{
	return
		alda::raw::stream::return_<
			Stream
		>(
			alda::raw::record<
				Types
			>(
				std::forward<
					Args
				>(
					_args
				)...
			)
		);
}

template<
	typename Types,
	typename Stream,
	typename Iterator,
	typename EndIterator,
	typename... Args
>
inline
typename
boost::disable_if<
	std::is_same<
		Iterator,
		EndIterator
	>,
	alda::raw::stream::result<
		Stream,
		alda::raw::record<
			Types
		>
	>
>::type
read(
	alda::raw::stream::reference<
		Stream
	> _stream,
	Args &&..._args
)
{
	typedef
	typename
	boost::mpl::deref<
		Iterator
	>::type
	role;

	return
		alda::raw::stream::bind<
			Stream
		>(
			alda::raw::make_generic<
				Stream,
				fcppt::record::element_to_type<
					role
				>
			>(
				_stream
			),
			[
				&_stream,
				&_args...
			](
				alda::raw::element_type<
					fcppt::record::element_to_type<
						role
					>
				> &&_arg
			)
			{
				return
					alda::raw::detail::read<
						Types,
						Stream,
						typename
						boost::mpl::next<
							Iterator
						>::type,
						EndIterator
					>(
						_stream,
						std::forward<
							Args
						>(
							_args
						)...,
						fcppt::record::element_to_label<
							role
						>{} =
							std::move(
								_arg
							)
					);
			}
		);
}

}

template<
	typename Types,
	typename Stream
>
inline
alda::raw::stream::result<
	Stream,
	alda::raw::record<
		Types
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::raw::record<
			Types
		>
	>,
	alda::raw::dispatch_type<
		Stream
	>,
	alda::raw::stream::reference<
		Stream
	> _stream
)
{
	return
		alda::raw::detail::read<
			Types,
			Stream,
			typename
			boost::mpl::begin<
				Types
			>::type,
			typename
			boost::mpl::end<
				Types
			>::type
		>(
			_stream
		);
}

}
}

#endif
