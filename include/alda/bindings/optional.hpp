//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED
#define ALDA_BINDINGS_OPTIONAL_HPP_INCLUDED

#include <alda/bindings/bool.hpp>
#include <alda/bindings/optional_decl.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/make.hpp>
#include <majutsu/needed_size.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
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
	fcppt::optional<
		Type
	> const &_opt_value,
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
		_opt_value.has_value()
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

	fcppt::maybe_void(
		_opt_value,
		[
			_mem
		](
			Type const &_value
		)
		{
			majutsu::place<
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
fcppt::optional<
	Type
>
make(
	majutsu::dispatch_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	>,
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
	majutsu::dispatch_type<
		alda::bindings::optional<
			Type,
			Adapted
		>
	>,
	fcppt::optional<
		Type
	> const &_opt_value
)
{
	typedef
	alda::bindings::optional<
		Type,
		Adapted
	>
	tag;

	typename tag::bool_type::type const has_value(
		_opt_value.has_value()
	);

	majutsu::size_type ret(
		majutsu::needed_size<
			typename tag::bool_type
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
					majutsu::needed_size<
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
