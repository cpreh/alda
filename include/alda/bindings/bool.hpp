//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_BOOL_HPP_INCLUDED
#define ALDA_BINDINGS_BOOL_HPP_INCLUDED

#include <alda/bindings/bool_decl.hpp>
#include <alda/bindings/unsigned.hpp>
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
#include <fcppt/literal.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

inline
void
place(
	majutsu::dispatch_type<
		alda::bindings::bool_
	>,
	majutsu::raw::element_type<
		alda::bindings::bool_
	> const _value,
	majutsu::raw::pointer const _data
)
{
	majutsu::raw::place<
		alda::bindings::bool_::wrapped_type
	>(
		_value
		?
			fcppt::literal<
				majutsu::raw::element_type<
					alda::bindings::bool_::wrapped_type
				>
			>(
				1
			)
		:
			fcppt::literal<
				majutsu::raw::element_type<
					alda::bindings::bool_::wrapped_type
				>
			>(
				0
			)
		,
		_data
	);
}

inline
majutsu::raw::element_type<
	alda::bindings::bool_
>
make(
	majutsu::dispatch_type<
		alda::bindings::bool_
	>,
	majutsu::raw::const_pointer const _data
)
{
	return
		majutsu::raw::make<
			alda::bindings::bool_::wrapped_type
		>(
			_data
		)
		!=
		fcppt::literal<
			majutsu::raw::element_type<
				alda::bindings::bool_::wrapped_type
			>
		>(
			0
		);
}

template<
	typename Stream
>
majutsu::raw::stream::result<
	Stream,
	alda::bindings::bool_
>
make_generic(
	majutsu::dispatch_type<
		alda::bindings::bool_
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
				alda::bindings::bool_::wrapped_type
			>(
				_stream
			),
			[](
				majutsu::raw::element_type<
					alda::bindings::bool_::wrapped_type
				> const _element
			)
			{
				return
					majutsu::raw::stream::return_<
						Stream
					>(
						_element
						!=
						fcppt::literal<
							majutsu::raw::element_type<
								alda::bindings::bool_::wrapped_type
							>
						>(
							0
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

template<>
struct static_size<
	alda::bindings::bool_
>
:
majutsu::raw::static_size<
	alda::bindings::bool_::wrapped_type
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
