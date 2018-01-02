//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_SIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_SIGNED_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/bindings/signed_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/static_size_impl.hpp>
#include <alda/raw/stream/bind.hpp>
#include <alda/raw/stream/reference.hpp>
#include <alda/raw/stream/result.hpp>
#include <alda/raw/stream/return.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <type_traits>
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
		alda::bindings::signed_<
			Type,
			Endianness
		>
	>,
	Type const &_value,
	alda::raw::pointer const _mem
)
{
	typedef
	typename
	std::make_unsigned<
		Type
	>::type
	unsigned_type;

	Type const null(
		fcppt::literal<
			Type
		>(
			0
		)
	);

	bool const is_negative(
		_value
		<
		null
	);

	Type const max(
		std::numeric_limits<
			Type
		>::max()
	);

	if(
		is_negative
		&&
		(
			_value + max
			<
			null
		)
	)
		throw alda::exception(
			FCPPT_TEXT("alda::bindings::signed has encountered a negative value")
			FCPPT_TEXT(" whose magnitude is larger than the largest positive value!")
		);

	unsigned_type const converted(
		is_negative
		?
			static_cast<
				unsigned_type
			>(
				static_cast<
					unsigned_type
				>(
					-_value
				)
				+
				static_cast<
					unsigned_type
				>(
					max
				)
			)
		:
			static_cast<
				unsigned_type
			>(
				_value
			)
	);

	alda::raw::place<
		alda::bindings::unsigned_<
			unsigned_type,
			Endianness
		>
	>(
		converted,
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
	alda::bindings::signed_<
		Type,
		Endianness
	>
>
make_generic(
	alda::raw::dispatch_type<
		alda::bindings::signed_<
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
	typedef
	typename
	alda::bindings::signed_<
		Type,
		Endianness
	>::impl
	unsigned_impl;

	typedef
	alda::raw::element_type<
		unsigned_impl
	>
	unsigned_type;

	return
		alda::raw::stream::bind<
			Stream
		>(
			alda::raw::make_generic<
				Stream,
				unsigned_impl
			>(
				_stream
			),
			[](
				unsigned_type const _converted
			)
			{
				Type const max(
					std::numeric_limits<
						Type
					>::max()
				);

				unsigned_type const converted_max(
					static_cast<
						unsigned_type
					>(
						max
					)
				);

				return
					alda::raw::stream::return_<
						Stream
					>(
						_converted
						>
						converted_max
						?
							static_cast<
								Type
							>(
								-
								static_cast<
									Type
								>(
									_converted
									-
									converted_max
								)
							)
						:
							static_cast<
								Type
							>(
								_converted
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
	alda::bindings::signed_<
		Type,
		Endianness
	>
>
:
alda::raw::static_size_impl<
	typename
	alda::bindings::signed_<
		Type,
		Endianness
	>::impl
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
