//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/bindings/fundamental.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/element_type.hpp>
#include <majutsu/raw/make.hpp>
#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
fixed_int;

typedef
majutsu::raw::element_type<
	alda::bindings::float_
>
float_type;

typedef
alda::bindings::fundamental<
	fixed_int
>
adapted;

fixed_int const sign_bit(
	0x1u
);

float_type const exp(
	fcppt::cast::int_to_float<
		float_type
	>(
		1ul << 16
	)
);

fixed_int
make_fixed(
	float_type const _val
)
{
	return
		static_cast<
			fixed_int
		>(
			std::log(
				_val
				+
				fcppt::literal<
					float_type
				>(
					1
				)
			)
			* exp
		);
}

float_type
unmake_fixed(
	fixed_int const _val
)
{
	return
		std::exp(
			fcppt::cast::int_to_float<
				float_type
			>(
				_val
			)
			/ exp
		)
		-
		fcppt::literal<
			float_type
		>(
			1
		);
}

fixed_int
serialize(
	float_type const _val
)
{
	return
		_val < 0
		?
			make_fixed(
				-_val
			)
			| sign_bit
		:
			make_fixed(
				_val
			)
			& ~sign_bit;
}

float_type
deserialize(
	fixed_int _val
)
{
	bool const is_signed(
		_val & sign_bit
	);

	_val &= ~sign_bit;

	return
		is_signed
		?
			unmake_fixed(
				_val
			)
			*
			fcppt::literal<
				float_type
			>(
				-1
			)
		:
			unmake_fixed(
				_val
			);
}

}

majutsu::raw::size_type
alda::bindings::needed_size(
	majutsu::dispatch_type<
		alda::bindings::float_
	>,
	majutsu::raw::element_type<
		alda::bindings::float_
	> const &
)
{
	return
		sizeof(
			fixed_int
		);
}

void
alda::bindings::place(
	majutsu::dispatch_type<
		alda::bindings::float_
	>,
	majutsu::raw::element_type<
		alda::bindings::float_
	> const &_val,
	majutsu::raw::pointer const _mem
)
{
	majutsu::raw::place<
		adapted
	>(
		serialize(
			_val
		),
		_mem
	);
}

majutsu::raw::element_type<
	alda::bindings::float_
>
alda::bindings::make(
	majutsu::dispatch_type<
		alda::bindings::float_
	>,
	majutsu::raw::const_pointer const _beg
)
{
	return
		deserialize(
			majutsu::raw::make<
				adapted
			>(
				_beg
			)
		);
}
