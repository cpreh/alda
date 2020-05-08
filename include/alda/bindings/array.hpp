//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ARRAY_HPP_INCLUDED
#define ALDA_BINDINGS_ARRAY_HPP_INCLUDED

#include <alda/bindings/array_decl.hpp>
#include <alda/raw/combine_static_sizes.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/container/array/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <cstddef>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
void
place(
	alda::raw::dispatch_type<
		alda::bindings::array<
			Type,
			Adapted
		>
	>,
	alda::raw::element_type<
		alda::bindings::array<
			Type,
			Adapted
		>
	> const &_value,
	alda::raw::pointer _mem
)
{
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
	typename Adapted
>
alda::raw::stream::result<
	Stream,
	alda::bindings::array<
		Type,
		Adapted
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::bindings::array<
			Type,
			Adapted
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
	result_type
	=
	alda::raw::stream::result<
		Stream,
		alda::bindings::array<
			Type,
			Adapted
		>
	>;

	// TODO(philipp): Improve this by breaking out early
	// TODO(philipp): We should fold the array
	return
		fcppt::algorithm::fold(
			fcppt::make_int_range_count(
				fcppt::container::array::size<
					Type
				>::value
			),
			alda::raw::stream::return_<
				Stream
			>(
				alda::raw::element_type<
					alda::bindings::array<
						Type,
						Adapted
					>
				>()
			),
			[
				&_stream
			](
				std::size_t const _index,
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
							&_stream,
							_index
						](
							Type &&_array
						)
						{
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
										&_array,
										_index
									](
										alda::raw::element_type<
											Adapted
										> &&_elem
									)
									{
										_array[
											_index
										] =
											std::move(
												_elem
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
						}
					);
				}
			);
}

}
}

namespace alda
{
namespace raw
{

template<
	typename Type,
	typename Adapted
>
struct static_size_impl<
	alda::bindings::array<
		Type,
		Adapted
	>
>
:
alda::raw::combine_static_sizes<
	metal::lambda<
		metal::mul
	>,
	fcppt::container::array::size<
		Type
	>,
	alda::raw::static_size<
		Adapted
	>
>
{
};

}
}

#endif
