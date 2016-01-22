//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/float.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/dispatch_type.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/place.hpp>
#include <alda/raw/pointer.hpp>
#include <alda/raw/stream/memory.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace
{

constexpr fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
alda::raw::element_type<
	alda::bindings::float_
>
float_type;

typedef
alda::bindings::float_::fixed_int
fixed_int;

typedef
alda::bindings::unsigned_<
	fixed_int,
	endianness
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

void
alda::bindings::place(
	alda::raw::dispatch_type<
		alda::bindings::float_
	>,
	alda::raw::element_type<
		alda::bindings::float_
	> const &_val,
	alda::raw::pointer const _mem
)
{
	alda::raw::place<
		adapted
	>(
		serialize(
			_val
		),
		_mem
	);
}

alda::raw::element_type<
	alda::bindings::float_
>
alda::bindings::make_float(
	alda::raw::const_pointer _beg
)
{
	return
		deserialize(
			alda::raw::make_generic<
				alda::raw::stream::memory,
				adapted
			>(
				_beg
			)
		);
}
