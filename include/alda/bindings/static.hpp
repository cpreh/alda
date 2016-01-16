//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_STATIC_HPP_INCLUDED
#define ALDA_BINDINGS_STATIC_HPP_INCLUDED

#include <alda/bindings/array.hpp>
#include <alda/bindings/static_decl.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/static_size.hpp>
#include <majutsu/raw/stream/bind.hpp>
#include <majutsu/raw/stream/reference.hpp>
#include <majutsu/raw/stream/result.hpp>
#include <majutsu/raw/stream/return.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
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
inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::static_<
			Type,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::static_<
			Type,
			Adapted
		>
	> const &_value,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		alda::bindings::array<
			typename
			Type::storage_type,
			Adapted
		>
	>(
		_value.storage(),
		_mem
	);
}

template<
	typename Type,
	typename Adapted
>
majutsu::raw::element_type<
	alda::bindings::static_<
		Type,
		Adapted
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::static_<
			Type,
			Adapted
		>
	>,
	majutsu::raw::const_pointer const _mem
)
{
	return
		Type(
			majutsu::raw::make<
				alda::bindings::array<
					typename
					Type::storage_type,
					Adapted
				>
			>(
				_mem
			)
		);
}

template<
	typename Stream,
	typename Type,
	typename Adapted
>
majutsu::raw::stream::result<
	Stream,
	alda::bindings::static_<
		Type,
		Adapted
	>
>
make_generic(
	majutsu::dispatch_type<
		alda::bindings::static_<
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
	typename
	Type::storage_type
	array_type;

	return
		majutsu::raw::stream::bind<
			Stream
		>(
			majutsu::raw::make_generic<
				Stream,
				alda::bindings::array<
					array_type,
					Adapted
				>
			>(
				_stream
			),
			[](
				array_type &&_result
			)
			{
				return
					majutsu::raw::stream::return_<
						Stream
					>(
						Type(
							std::move(
								_result
							)
						)
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
	alda::bindings::static_<
		Type,
		Adapted
	>
>
:
majutsu::raw::static_size<
	alda::bindings::array<
		typename
		Type::storage_type,
		Adapted
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
