//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ARRAY_HPP_INCLUDED
#define ALDA_BINDINGS_ARRAY_HPP_INCLUDED

#include <alda/bindings/array_decl.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/integral_size.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <majutsu/raw/static_size.hpp>
#include <majutsu/raw/stream/bind.hpp>
#include <majutsu/raw/stream/reference.hpp>
#include <majutsu/raw/stream/result.hpp>
#include <majutsu/raw/stream/return.hpp>
#include <fcppt/tag_value.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/array_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <boost/mpl/range_c.hpp>
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
	majutsu::dispatch_type<
		alda::bindings::array<
			Type,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::array<
			Type,
			Adapted
		>
	> const &_value,
	majutsu::raw::pointer _mem
)
{
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
	typename Adapted
>
majutsu::raw::element_type<
	alda::bindings::array<
		Type,
		Adapted
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::array<
			Type,
			Adapted
		>
	>,
	majutsu::raw::const_pointer _mem
)
{
	// TODO: We should fold the array here
	Type ret;

	for(
		auto &elem
		:
		ret
	)
	{
		elem =
			majutsu::raw::make<
				Adapted
			>(
				_mem
			);

		_mem +=
			majutsu::raw::needed_size<
				Adapted
			>(
				elem
			);
	}

	return
		ret;
}

template<
	typename Stream,
	typename Type,
	typename Adapted
>
majutsu::raw::stream::result<
	Stream,
	alda::bindings::array<
		Type,
		Adapted
	>
>
make_generic(
	majutsu::dispatch_type<
		alda::bindings::array<
			Type,
			Adapted
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
		alda::bindings::array<
			Type,
			Adapted
		>
	>
	result_type;

	// TODO: Improve this by breaking out early
	// TODO: We should fold the array
	return
		fcppt::algorithm::fold(
			boost::mpl::range_c<
				std::size_t,
				0,
				fcppt::container::array_size<
					Type
				>::value
			>{},
			majutsu::raw::stream::return_<
				Stream
			>(
				majutsu::raw::element_type<
					alda::bindings::array<
						Type,
						Adapted
					>
				>()
			),
			[
				&_stream
			](
				auto const _index,
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
							&_stream,
							_index
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
										&_array,
										_index
									](
										majutsu::raw::element_type<
											Adapted
										> &&_elem
									)
									{
										std::get<
											fcppt::tag_value(
												_index
											)
										>(
											_array
										) =
											std::move(
												_elem
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

}
}

namespace majutsu
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type,
	typename Adapted
>
struct static_size<
	alda::bindings::array<
		Type,
		Adapted
	>
>
:
// FIXME: We have to check if Type has a static size
majutsu::raw::integral_size<
	// Can't use mpl::multiplies here because std::integral_constant doesn't work
	fcppt::cast::size<
		majutsu::raw::size_type
	>(
		fcppt::container::array_size<
			Type
		>::value
	)
	*
	majutsu::raw::static_size<
		Adapted
	>::value
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
