//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/bindings/length_count_policy.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/needed_size_static.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <majutsu/raw/stream/bind.hpp>
#include <majutsu/raw/stream/reference.hpp>
#include <majutsu/raw/stream/result.hpp>
#include <majutsu/raw/stream/return.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/truncation_check.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	> const &_value
)
{
	majutsu::raw::size_type ret(
		majutsu::raw::needed_size_static<
			Length
		>()
	);

	for(
		auto const &elem
		:
		_value
	)
		ret +=
			majutsu::raw::needed_size<
				Adapted
			>(
				elem
			);

	return
		ret;
}

template<
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
void
place(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	> const &_value,
	majutsu::raw::pointer _mem
)
{
	{
		typedef
		majutsu::raw::element_type<
			Length
		>
		length_type;

		length_type const length(
			fcppt::cast::truncation_check<
				length_type
			>(
				LengthPolicy::place(
					_value
				)
			)
		);

		majutsu::raw::place<
			Length
		>(
			length,
			_mem
		);

		_mem +=
			majutsu::raw::needed_size<
				Length
			>(
				length
			);
	}

	for(
		auto const &elem
		:
		_value
	)
	{
		majutsu::raw::place<
			Adapted
		>(
			elem,
			_mem
		);

		_mem +=
			majutsu::raw::needed_size<
				Adapted
			>(
				elem
			);
	}
}

template<
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
majutsu::raw::element_type<
	alda::bindings::dynamic_len<
		Type,
		Adapted,
		Length,
		LengthPolicy
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>,
	majutsu::raw::const_pointer const _mem
)
{
	majutsu::raw::element_type<
		Length
	> const num_elements(
		LengthPolicy::make(
			majutsu::raw::make<
				Length
			>(
				_mem
			)
		)
	);

	majutsu::raw::const_pointer cur_mem(
		_mem
		+
		majutsu::raw::needed_size_static<
			Length
		>()
	);

	return
		fcppt::algorithm::map<
			Type
		>(
			fcppt::make_int_range_count(
				num_elements
			),
			[
				&cur_mem
			](
				majutsu::raw::element_type<
					Length
				>
			)
			{
				typename
				Type::value_type elem(
					majutsu::raw::make<
						Adapted
					>(
						cur_mem
					)
				);

				cur_mem +=
					majutsu::raw::needed_size<
						Adapted
					>(
						elem
					);

				return
					elem;
			}
		);
}

template<
	typename Stream,
	typename Type,
	typename Adapted,
	typename Length,
	typename LengthPolicy
>
majutsu::raw::stream::result<
	Stream,
	alda::bindings::dynamic_len<
		Type,
		Adapted,
		Length,
		LengthPolicy
	>
>
make_generic(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>,
	majutsu::dispatch_type<
		Stream
	>,
	majutsu::raw::stream::reference<
		Stream
	> _stream
)
{
	typedef
	majutsu::raw::stream::result<
		Stream,
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length,
			LengthPolicy
		>
	>
	result_type;

	return
		majutsu::raw::stream::bind<
			Stream
		>(
			majutsu::raw::make_generic<
				Stream,
				Length
			>(
				_stream
			),
			[
				&_stream
			](
				majutsu::raw::element_type<
					Length
				> const _my_size
			)
			{
				// TODO: Break out early
				// TODO: reserve the output size
				return
					fcppt::algorithm::fold(
						fcppt::make_int_range_count(
							LengthPolicy::make(
								_my_size
							)
						),
						majutsu::raw::stream::return_<
							Stream
						>(
							majutsu::raw::element_type<
								alda::bindings::dynamic_len<
									Type,
									Adapted,
									Length,
									LengthPolicy
								>
							>()
						),
						[
							&_stream
						](
							majutsu::raw::element_type<
								Length
							>,
							result_type &&_result
						)
						{
							return
								majutsu::raw::stream::bind<
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
										return
											majutsu::raw::stream::bind<
												Stream
											>(
												majutsu::raw::make_generic<
													Stream,
													Adapted
												>(
													_stream
												),
												[
													&_array
												](
													majutsu::raw::element_type<
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
														majutsu::raw::stream::return_<
															Stream
														>(
															std::move(
																_array
															)
														);
												}
											);
									}
								);
						}
					);
			}
		);

}


}
}

#endif
