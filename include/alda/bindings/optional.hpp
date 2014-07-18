//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED
#define ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED

#include <alda/bindings/bool.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/needed_size.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <fcppt/optional_impl.hpp>


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
	alda::bindings::optional<
		Type,
		Adapted
	> const *,
	fcppt::optional<
		Type
	> const _value,
	majutsu::raw_pointer _mem
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	tag;

	typename tag::bool_type::type const has_value(
		_value.has_value()
	);

	majutsu::place<
		typename tag::bool_type
	>(
		has_value,
		_mem
	);

	_mem +=
		majutsu::needed_size<
			typename tag::bool_type
		>(
			has_value
		);

	if(
		_value.has_value()
	)
		majutsu::place<
			Adapted
		>(
			*_value,
			_mem
		);
}

template<
	typename Type,
	typename Adapted
>
fcppt::optional<
	Type
>
make(
	alda::bindings::optional<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer _mem
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	tag;

	typename tag::bool_type::type const has_value(
		majutsu::make<
			typename tag::bool_type
		>(
			_mem
		)
	);

	if(
		!has_value
	)
		return
			fcppt::optional<
				Type
			>();

	_mem +=
		majutsu::needed_size<
			typename tag::bool_type
		>(
			has_value
		);

	return
		fcppt::optional<
			Type
		>(
			majutsu::make<
				Adapted
			>(
				_mem
			)
		);
}

template<
	typename Type,
	typename Adapted
>
majutsu::size_type
needed_size(
	alda::bindings::optional<
		Type,
		Adapted
	> const *,
	fcppt::optional<
		Type
	> const _value
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	tag;

	typename tag::bool_type::type const has_value(
		_value.has_value()
	);

	majutsu::size_type ret(
		majutsu::needed_size<
			typename tag::bool_type
		>(
			has_value
		)
	);

	if(
		_value.has_value()
	)
		ret +=
			majutsu::needed_size<
				Adapted
			>(
				*_value
			);

	return
		ret;
}

}
}

#endif
