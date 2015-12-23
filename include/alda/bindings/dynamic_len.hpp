//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/cast/truncation_check.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted,
	typename Length
>
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
		>
	> const &_value
)
{
	majutsu::raw::size_type ret(
		// TODO: needed_size?
		sizeof(
			majutsu::raw::element_type<
				Length
			>
		)
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
	typename Length
>
void
place(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
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
				majutsu::raw::needed_size<
					alda::bindings::dynamic_len<
						Type,
						Adapted,
						Length
					>
				>(
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
	typename Length
>
majutsu::raw::element_type<
	alda::bindings::dynamic_len<
		Type,
		Adapted,
		Length
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted,
			Length
		>
	>,
	majutsu::raw::const_pointer const _mem
)
{
	majutsu::raw::element_type<
		Length
	> const my_size(
		majutsu::raw::make<
			Length
		>(
			_mem
		)
	);

	Type ret;

	for(
		majutsu::raw::const_pointer cur_mem(
			_mem
			+
			majutsu::raw::needed_size<
				Length
			>(
				my_size
			)
		);
		cur_mem != _mem + my_size;
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

		ret.push_back(
			elem
		);

		cur_mem +=
			majutsu::raw::needed_size<
				Adapted
			>(
				elem
			);
	}

	return
		ret;
}

}
}

#endif
