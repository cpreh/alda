//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_VARIANT_HPP_INCLUDED
#define ALDA_BINDINGS_VARIANT_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant_decl.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/fail.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/use.hpp>
#include <fcppt/cast/promote_int.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/list/index_of.hpp>
#include <fcppt/mpl/list/invoke_on.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Types,
	typename AdaptedTypes
>
void
place(
	alda::raw::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	alda::raw::element_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	> const &_value,
	alda::raw::pointer _mem
)
{
	using
	binding
	=
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>;

	using
	index_type
	=
	typename
	binding::index_type;

	auto const index(
		fcppt::optional::to_exception(
			fcppt::cast::truncation_check<
				alda::raw::element_type<
					index_type
				>
			>(
				_value.type_index()
			),
			[]{
				return
					alda::exception{
						FCPPT_TEXT("variant index too large")
					};
			}
		)
	);

	_mem =
		alda::raw::place_and_update<
			index_type
		>(
			index,
			_mem
		);

	fcppt::variant::apply(
		[
			_mem
		](
			auto const &_type
		)
		{
			alda::raw::place<
				fcppt::mpl::list::at<
					AdaptedTypes,
					fcppt::mpl::list::index_of<
						Types,
						std::decay_t<
							decltype(
								_type
							)
						>
					>
				>
			>(
				_type,
				_mem
			);
		},
		_value
	);
}

template<
	typename Stream,
	typename Types,
	typename AdaptedTypes
>
alda::raw::stream::result<
	Stream,
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
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
	using
	binding
	=
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>;

	using
	index_type
	=
	typename
	binding::index_type;

	return
		alda::raw::stream::bind<
			Stream
		>(
			alda::raw::make_generic<
				Stream,
				index_type
			>(
				_stream
			),
			[
				&_stream
			](
				alda::raw::element_type<
					index_type
				> const _index
			)
			{
				return
					fcppt::mpl::list::invoke_on<
						Types
					>(
						_index,
						[
							&_stream
						](
							auto const _tag
						)
						{
							FCPPT_USE(
								_tag
							);

							using
							adapted_type
							=
							fcppt::mpl::list::at<
								AdaptedTypes,
								fcppt::mpl::list::index_of<
									Types,
									fcppt::tag_type<
										decltype(
											_tag
										)
									>
								>
							>;

							return
								alda::raw::stream::bind<
									Stream
								>(
									alda::raw::make_generic<
										Stream,
										adapted_type
									>(
										_stream
									),
									[](
										alda::raw::element_type<
											adapted_type
										> &&_inner
									)
									{
										return
											alda::raw::stream::return_<
												Stream
											>(
												fcppt::variant::from_list<
													Types
												>(
													std::move(
														_inner
													)
												)
											);
									}
								);
						},
						[
							_index
						]
						{
							return
								alda::raw::stream::fail<
									Stream,
									alda::bindings::variant<
										Types,
										AdaptedTypes
									>
								>(
									FCPPT_TEXT("Invalid index: ")
									+
									fcppt::output_to_fcppt_string(
										fcppt::cast::promote_int(
											_index
										)
									)
								);
						}
					);
			}
		);
}


template<
	typename Types,
	typename AdaptedTypes
>
alda::raw::size_type
needed_size(
	alda::raw::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	alda::raw::element_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	> const &_value
)
{
	using
	binding
	=
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>;

	using
	index_type
	=
	typename
	binding::index_type;

	auto const index(
		fcppt::optional::to_exception(
			fcppt::cast::truncation_check<
				alda::raw::element_type<
					index_type
				>
			>(
				_value.type_index()
			),
			[]{
				return
					alda::exception{
						FCPPT_TEXT("variant index too large")
					};
			}
		)
	);

	return
		alda::raw::needed_size<
			index_type
		>(
			index
		)
		+
		fcppt::variant::apply(
			[](
				auto const &_type
			)
			{
				return
					alda::raw::needed_size<
						fcppt::mpl::list::at<
							AdaptedTypes,
							fcppt::mpl::list::index_of<
								Types,
								std::decay_t<
									decltype(
										_type
									)
								>
							>
						>
					>(
						_type
					);
			},
			_value
		);
}

}
}

#endif
