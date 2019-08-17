//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_RECORD_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_HPP_INCLUDED

#include <alda/bindings/record_decl.hpp>
#include <alda/raw/combine_static_sizes.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/place_and_update.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/size_type.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_brigand.hpp>
#include <fcppt/record/element_to_label.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/fold.hpp>
#include <brigand/functions/arithmetic/plus.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/at.hpp>
#include <brigand/sequences/size.hpp>
#include <brigand/types/args.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

template<
	typename Types
>
struct static_size_impl<
	alda::bindings::record<
		Types
	>
>
{
	typedef
	brigand::fold<
		Types,
		alda::raw::integral_size<
			0
		>,
		brigand::bind<
			alda::raw::combine_static_sizes,
			brigand::defer<
				brigand::plus<
					brigand::_1,
					brigand::_2
				>
			>,
			brigand::bind<
				alda::raw::static_size,
				brigand::bind<
					fcppt::record::element_to_type,
					brigand::_element
				>
			>,
			brigand::_state
		>
	>
	type;
};

}

namespace bindings
{

template<
	typename Types
>
alda::raw::size_type
needed_size(
	alda::raw::dispatch_type<
		alda::bindings::record<
			Types
		>
	>,
	alda::raw::element_type<
		alda::bindings::record<
			Types
		>
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
						fcppt::record::get<
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
		alda::bindings::record<
			Types
		>
	>,
	alda::raw::element_type<
		alda::bindings::record<
			Types
		>
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

			_memory =
				alda::raw::place_and_update<
					fcppt::record::element_to_type<
						role
					>
				>(
					fcppt::record::get<
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
	unsigned Index,
	unsigned MaxIndex,
	typename... Args
>
inline
typename
std::enable_if<
	Index
	==
	MaxIndex,
	alda::raw::stream::result<
		Stream,
		alda::bindings::record<
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
			alda::raw::element_type<
				alda::bindings::record<
					Types
				>
			>{
				std::forward<
					Args
				>(
					_args
				)...
			}
		);
}

template<
	typename Types,
	typename Stream,
	unsigned Index,
	unsigned MaxIndex,
	typename... Args
>
inline
typename
std::enable_if<
	Index
	!=
	MaxIndex,
	alda::raw::stream::result<
		Stream,
		alda::bindings::record<
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
	brigand::at_c<
		Types,
		Index
	>
	element;

	return
		alda::raw::stream::bind<
			Stream
		>(
			alda::raw::make_generic<
				Stream,
				fcppt::record::element_to_type<
					element
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
						element
					>
				> &&_arg
			)
			{
				return
					alda::bindings::detail::read<
						Types,
						Stream,
						Index + 1u,
						MaxIndex
					>(
						_stream,
						std::forward<
							Args
						>(
							_args
						)...,
						fcppt::record::element_to_label<
							element
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
	alda::bindings::record<
		Types
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::bindings::record<
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
		alda::bindings::detail::read<
			Types,
			Stream,
			0u,
			brigand::size<
				Types
			>::value
		>(
			_stream
		);
}

}
}

#endif
