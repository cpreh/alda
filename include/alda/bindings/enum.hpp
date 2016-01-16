//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_ENUM_HPP_INCLUDED
#define ALDA_BINDINGS_ENUM_HPP_INCLUDED

#include <alda/bindings/enum_decl.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/static_size.hpp>
#include <majutsu/raw/stream/bind.hpp>
#include <majutsu/raw/stream/reference.hpp>
#include <majutsu/raw/stream/result.hpp>
#include <majutsu/raw/stream/return.hpp>
#include <fcppt/cast_to_enum.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Enum,
	typename Adapted
>
inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::enum_<
			Enum,
			Adapted
		>
	>,
	majutsu::raw::element_type<
		alda::bindings::enum_<
			Enum,
			Adapted
		>
	> const &_enum,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		Adapted
	>(
		fcppt::cast::enum_to_int<
			majutsu::raw::element_type<
				Adapted
			>
		>(
			_enum
		),
		_mem
	);
}

template<
	typename Enum,
	typename Adapted
>
inline
majutsu::raw::element_type<
	alda::bindings::enum_<
		Enum,
		Adapted
	>
>
make(
	majutsu::dispatch_type<
		alda::bindings::enum_<
			Enum,
			Adapted
		>
	>,
	majutsu::raw::const_pointer const _beg
)
{
	return
		fcppt::cast_to_enum<
			Enum
		>(
			majutsu::raw::make<
				Adapted
			>(
				_beg
			)
		);
}

template<
	typename Stream,
	typename Enum,
	typename Adapted
>
inline
majutsu::raw::stream::result<
	Stream,
	alda::bindings::enum_<
		Enum,
		Adapted
	>
>
make_generic(
	majutsu::dispatch_type<
		alda::bindings::enum_<
			Enum,
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
	return
		majutsu::raw::stream::bind<
			Stream
		>(
			majutsu::raw::make_generic<
				Stream,
				Adapted
			>(
				_stream
			),
			[](
				majutsu::raw::element_type<
					Adapted
				> const _element
			)
			{
				return
					majutsu::raw::stream::return_<
						Stream
					>(
						fcppt::cast_to_enum<
							Enum
						>(
							_element
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
	typename Enum,
	typename Adapted
>
struct static_size<
	alda::bindings::enum_<
		Enum,
		Adapted
	>
>
:
majutsu::raw::static_size<
	Adapted
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
