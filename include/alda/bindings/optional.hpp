//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED
#define ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED

#include <alda/bindings/bool.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
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
	majutsu::dispatch_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	> const &_opt_value,
	majutsu::raw::pointer _mem
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	binding;

	typedef
	typename
	binding::bool_type
	bool_type;

	majutsu::raw::element_type<
		bool_type
	> const has_value(
		_opt_value.has_value()
	);

	majutsu::raw::place<
		bool_type
	>(
		has_value,
		_mem
	);

	_mem +=
		majutsu::raw::needed_size<
			bool_type
		>(
			has_value
		);

	fcppt::maybe_void(
		_opt_value,
		[
			_mem
		](
			Type const &_value
		)
		{
			majutsu::raw::place<
				Adapted
			>(
				_value,
				_mem
			);
		}
	);
}

template<
	typename Type,
	typename Adapted
>
majutsu::raw::element_type<
	alda::bindings::optional<
		Type,
		Adapted
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	>,
	majutsu::raw::const_pointer _mem
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	binding;

	typedef
	typename
	binding::bool_type
	bool_type;

	majutsu::raw::element_type<
		bool_type
	> const has_value(
		majutsu::raw::make<
			bool_type
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
		majutsu::raw::needed_size<
			bool_type
		>(
			has_value
		);

	return
		fcppt::optional<
			Type
		>(
			majutsu::raw::make<
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
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	> const &_opt_value
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	binding;

	typedef
	typename
	binding::bool_type
	bool_type;

	majutsu::raw::element_type<
		bool_type
	> const has_value(
		_opt_value.has_value()
	);

	majutsu::raw::size_type ret(
		majutsu::raw::needed_size<
			bool_type
		>(
			has_value
		)
	);

	return
		fcppt::maybe(
			_opt_value,
			fcppt::const_(
				ret
			),
			[
				ret
			](
				Type const &_value
			)
			{
				return
					ret
					+
					majutsu::raw::needed_size<
						Adapted
					>(
						_value
					);
			}
		);
}

}
}

#endif
