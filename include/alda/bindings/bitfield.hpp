//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_BITFIELD_HPP_INCLUDED
#define ALDA_BINDINGS_BITFIELD_HPP_INCLUDED

#include <alda/bindings/array.hpp>
#include <alda/bindings/bitfield_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/endianness/format_fwd.hpp>
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
	fcppt::endianness::format Endianness
>
void
place(
	alda::raw::dispatch_type<
		alda::bindings::bitfield<
			Type,
			Endianness
		>
	>,
	alda::raw::element_type<
		alda::bindings::bitfield<
			Type,
			Endianness
		>
	> const &_value,
	alda::raw::pointer const _mem
)
{
	alda::raw::place<
		typename
		alda::bindings::bitfield<
			Type,
			Endianness
		>::wrapped
	>(
		_value.array(),
		_mem
	);
}

template<
	typename Stream,
	typename Type,
	fcppt::endianness::format Endianness
>
alda::raw::stream::result<
	Stream,
	alda::bindings::bitfield<
		Type,
		Endianness
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::bindings::bitfield<
			Type,
			Endianness
		>
	>,
	alda::raw::dispatch_type<
		Stream
	>,
	alda::raw::stream::reference<
		Stream
	> _stream
)
{
	using
	wrapped
	=
	typename
	alda::bindings::bitfield<
		Type,
		Endianness
	>::wrapped;

	return
		alda::raw::stream::bind<
			Stream
		>(
			alda::raw::make_generic<
				Stream,
				wrapped
			>(
				_stream
			),
			[](
				alda::raw::element_type<
					wrapped
				> &&_inner
			)
			{
				return
					alda::raw::stream::return_<
						Stream
					>(
						Type(
							std::move(
								_inner
							)
						)
					);
			}
		);
}

}
}

namespace alda
{
namespace raw
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type,
	fcppt::endianness::format Endianness
>
struct static_size_impl<
	alda::bindings::bitfield<
		Type,
		Endianness
	>
>
:
alda::raw::static_size_impl<
	typename
	alda::bindings::bitfield<
		Type,
		Endianness
	>::wrapped
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
