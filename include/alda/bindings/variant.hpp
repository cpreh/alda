//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_VARIANT_HPP_INCLUDED
#define ALDA_BINDINGS_VARIANT_HPP_INCLUDED

#include <alda/bindings/invalid_variant.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant_decl.hpp>
#include <alda/bindings/detail/variant_make.hpp>
#include <alda/bindings/detail/variant_needed_size.hpp>
#include <alda/bindings/detail/variant_place.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/mpl/invoke_on.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


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
	majutsu::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	> const &_value,
	majutsu::raw::pointer _mem
)
{
	typedef
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
	binding;

	typedef
	typename
	binding::index_type
	index_type;

	auto const index(
		fcppt::cast::truncation_check<
			majutsu::raw::element_type<
				index_type
			>
		>(
			_value.type_index()
		)
	);

	majutsu::raw::place<
		index_type
	>(
		index,
		_mem
	);

	_mem +=
		majutsu::raw::needed_size<
			index_type
		>(
			index
		);

	fcppt::variant::apply_unary(
		alda::bindings::detail::variant_place<
			Types,
			AdaptedTypes
		>(
			_mem
		),
		_value
	);
}

template<
	typename Types,
	typename AdaptedTypes
>
majutsu::raw::element_type<
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	majutsu::raw::const_pointer _mem
)
{
	typedef
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
	binding;

	typedef
	typename
	binding::index_type
	index_type;

	auto const index(
		majutsu::raw::make<
			index_type
		>(
			_mem
		)
	);

	_mem +=
		majutsu::raw::needed_size<
			index_type
		>(
			index
		);

	return
		fcppt::mpl::invoke_on<
			Types
		>(
			index,
			alda::bindings::detail::variant_make<
				Types,
				AdaptedTypes
			>(
				_mem
			),
			[]()
			->
			fcppt::variant::object<
				Types
			>
			{
				throw
					alda::bindings::invalid_variant();
			}
		);
}

template<
	typename Types,
	typename AdaptedTypes
>
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	> const &_value
)
{
	typedef
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
	binding;

	typedef
	typename
	binding::index_type
	index_type;

	auto const index(
		fcppt::cast::truncation_check<
			majutsu::raw::element_type<
				index_type
			>
		>(
			_value.type_index()
		)
	);

	return
		majutsu::raw::needed_size<
			index_type
		>(
			index
		)
		+
		fcppt::variant::apply_unary(
			alda::bindings::detail::variant_needed_size<
				Types,
				AdaptedTypes
			>(),
			_value
		);
}

}
}

#endif
