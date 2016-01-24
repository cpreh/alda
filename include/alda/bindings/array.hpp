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
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/container/array_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/placeholders.hpp>
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
		alda::raw::place_and_update<
			Adapted
		>(
			elem,
			_mem
		);
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
	typedef
	alda::raw::stream::result<
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
			fcppt::make_int_range_count(
				fcppt::container::array_size<
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
alda::raw::combine_static_sizes<
	boost::mpl::multiplies<
		boost::mpl::_1,
		boost::mpl::_2
	>,
	boost::mpl::integral_c<
		alda::raw::size_type,
		fcppt::container::array_size<
			Type
		>::value
	>,
	alda::raw::static_size<
		Adapted
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
