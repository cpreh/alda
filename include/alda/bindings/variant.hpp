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
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/make.hpp>
#include <majutsu/needed_size.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <fcppt/truncation_check_cast.hpp>
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
	fcppt::variant::object<
		Types
	> const _value,
	majutsu::raw_pointer _mem
)
{
	typedef
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
	tag;

	typedef
	typename
	tag::index_type::type
	index_type;

	index_type const index(
		fcppt::truncation_check_cast<
			index_type
		>(
			_value.type_index()
		)
	);

	majutsu::place<
		typename tag::index_type
	>(
		index,
		_mem
	);

	_mem +=
		majutsu::needed_size<
			typename tag::index_type
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
fcppt::variant::object<
	Types
>
make(
	majutsu::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	majutsu::const_raw_pointer _mem
)
{
	typedef
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
	tag;

	typename tag::index_type::type const index(
		majutsu::make<
			typename tag::index_type
		>(
			_mem
		)
	);

	_mem +=
		majutsu::needed_size<
			typename tag::index_type
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
majutsu::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::variant<
			Types,
			AdaptedTypes
		>
	>,
	fcppt::variant::object<
		Types
	> const _value
)
{
	typedef
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
	tag;

	typedef
	typename
	tag::index_type::type
	index_type;

	index_type const index(
		fcppt::truncation_check_cast<
			index_type
		>(
			_value.type_index()
		)
	);

	return
		majutsu::needed_size<
			typename tag::index_type
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
