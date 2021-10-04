//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/bindings/length_count_policy.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/needed_size_static.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda::bindings
{

template<
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
alda::raw::size_type
needed_size(
	alda::raw::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>,
	alda::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	> const &_value
)
{
	return
		fcppt::algorithm::fold(
			_value,
			alda::raw::needed_size_static<
				Length
			>(),
			[](
				alda::raw::element_type<
					Adapted
				> const &_element,
				alda::raw::size_type const _result
			)
			{
				return
					_result
					+
					alda::raw::needed_size<
						Adapted
					>(
						_element
					);
			}
		);
}

template<
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
void
place(
	alda::raw::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>,
	alda::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	> const &_value,
	alda::raw::pointer _mem
)
{
	_mem =
		alda::raw::place_and_update<
			Length
		>(
			fcppt::optional::to_exception(
				fcppt::cast::truncation_check<
					alda::raw::element_type<
						Length
					>
				>(
					LengthPolicy::place(
						_value
					)
				),
				[]{
					return
						alda::exception{
							FCPPT_TEXT("dynamic_len: size too large")
						};
				}
			),
			_mem
		);

	for(
		auto const &elem
		:
		_value
	)
	{
		_mem =
			alda::raw::place_and_update<
				Adapted
			>(
				elem,
				_mem
			);
	}
}

template<
	typename Stream,
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
alda::raw::stream::result<
	Stream,
	alda::bindings::dynamic_len<
		Type,
		Adapted,
		Length,
		LengthPolicy
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
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
	alda::bindings::dynamic_len<
		Type,
		Adapted,
		Length,
		LengthPolicy
	>;

	using
	result_type
	=
	alda::raw::stream::result<
		Stream,
		binding
	>;

	return
		alda::raw::stream::bind<
			Stream
		>(
			alda::raw::make_generic<
				Stream,
				Length
			>(
				_stream
			),
			[
				&_stream
			](
				alda::raw::element_type<
					Length
				> const _my_size
			)
			{
				// TODO(philipp): Break out early
				return
					fcppt::algorithm::fold(
						fcppt::make_int_range_count(
							LengthPolicy::make(
								_my_size
							)
						),
						[
							_my_size
						]{
							alda::raw::element_type<
								binding
							>
							result;

							result.reserve(
								_my_size
							);

							return
								alda::raw::stream::return_<
									Stream
								>(
									std::move(
										result
									)
								);
						}(),
						[
							&_stream
						](
							alda::raw::element_type<
								Length
							>,
							result_type &&_result
						)
						{
							return
								alda::raw::stream::bind<
									Stream
								>(
									std::move(
										_result
									),
									[
										&_stream
									](
										Type &&_array
									)
									{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
										return
											alda::raw::stream::bind<
												Stream
											>(
												alda::raw::make_generic<
													Stream,
													Adapted
												>(
													_stream
												),
												[
													&_array
												](
													alda::raw::element_type<
														Adapted
													> &&_element
												)
												{
													_array.push_back(
														std::move(
															_element
														)
													);

													return
														alda::raw::stream::return_<
															Stream
														>(
															std::move(
																_array
															)
														);
												}
											);
FCPPT_PP_POP_WARNING
									}
								);
						}
					);
			}
		);

}


}

#endif
