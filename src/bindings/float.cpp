//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/bindings/fundamental.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::uint32_t fixed_int;

typedef alda::bindings::float_::type float_type;

typedef alda::bindings::fundamental<
	fixed_int
> adapted;

fixed_int const sign_bit(
	0x1u
);

float_type const exp(
	static_cast<
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
				static_cast<
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
			static_cast<
				float_type
			>(
				_val
			)
			/ exp
		)
		- static_cast<
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
			* static_cast<
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

majutsu::size_type
alda::bindings::needed_size(
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &
)
{
	return sizeof(fixed_int);
}

void
alda::bindings::place(
	alda::bindings::float_ const *,
	alda::bindings::float_::type const &_val,
	majutsu::raw_pointer const _mem
)
{
	majutsu::place<
		adapted
	>(
		serialize(
			_val
		),
		_mem
	);
}

alda::bindings::float_::type
alda::bindings::make(
	alda::bindings::float_ const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		deserialize(
			majutsu::make<
				adapted
			>(
				_beg
			)
		);
}
