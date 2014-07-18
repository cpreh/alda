//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_SIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_SIGNED_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/bindings/signed_decl.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/static_size.hpp>
#include <fcppt/text.hpp>
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
	typename Type
>
void
place(
	alda::bindings::signed_<
		Type
	> const *,
	Type const &_value,
	majutsu::raw_pointer const _mem
)
{
	typedef typename std::make_unsigned<
		Type
	>::type unsigned_type;

	Type const null(
		static_cast<
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

	majutsu::place<
		alda::bindings::unsigned_<
			unsigned_type
		>
	>(
		converted,
		_mem
	);
}

template<
	typename Type
>
Type
make(
	alda::bindings::signed_<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	typedef typename std::make_unsigned<
		Type
	>::type unsigned_type;


	unsigned_type const converted(
		majutsu::make<
			alda::bindings::unsigned_<
				unsigned_type
			>
		>(
			_beg
		)
	);

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
		converted
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
					converted - converted_max
				)
			)
		:
			static_cast<
				Type
			>(
				converted
			)
		;
}

}
}

namespace majutsu
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct static_size<
	alda::bindings::signed_<
		Type
	>
>
:
majutsu::static_size<
	majutsu::fundamental<
		Type
	>
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
