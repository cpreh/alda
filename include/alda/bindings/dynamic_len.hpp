//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/dynamic_len_decl.hpp>
#include <alda/bindings/detail/extract_length.hpp>
#include <alda/bindings/detail/put_length.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted
		>
	> const &_value
)
{
	majutsu::raw::size_type ret(
		sizeof(
			typename
			alda::bindings::dynamic_len<
				Type,
				Adapted
			>::length_type
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

	return ret;
}

template<
	typename Type,
	typename Adapted
>
void
place(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted
		>
	> const _concept,
	majutsu::raw::element_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted
		>
	> const &_value,
	majutsu::raw::pointer _mem
)
{
	alda::bindings::detail::put_length(
		_concept,
		_value,
		_mem
	);

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
	alda::bindings::dynamic_len<
		Type,
		Adapted
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::dynamic_len<
			Type,
			Adapted
		>
	> const _concept,
	majutsu::raw::const_pointer const _mem
)
{
	typedef
	typename
	alda::bindings::dynamic_len<
		Type,
		Adapted
	>::length_type
	length_type;

	length_type const my_size(
		alda::bindings::detail::extract_length(
			_concept,
			_mem
		)
	);

	Type ret;

	for(
		majutsu::raw::const_pointer cur_mem(
			_mem + sizeof(length_type)
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
