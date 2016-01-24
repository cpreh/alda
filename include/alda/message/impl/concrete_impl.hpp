//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_IMPL_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_MESSAGE_IMPL_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/message/concrete_decl.hpp>
#include <alda/message/record_impl.hpp>
#include <alda/message/detail/extract_id.hpp>
#include <alda/raw/record_to_buffer.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/int_to_enum.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::concrete(
	Type &&_value
)
:
	base_type(),
	value_(
		std::move(
			_value
		)
	)
{
}

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::concrete(
	Type const &_value
)
:
	base_type(),
	value_(
		_value
	)
{
}

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::concrete(
	concrete const &
) = default;

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
> &
alda::message::concrete<
	TypeEnum,
	Type
>::operator=(
	concrete const &
) = default;

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::concrete(
	concrete &&
) = default;

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
> &
alda::message::concrete<
	TypeEnum,
	Type
>::operator=(
	concrete &&
) = default;

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::~concrete()
{
}

template<
	typename TypeEnum,
	typename Type
>
Type const &
alda::message::concrete<
	TypeEnum,
	Type
>::value() const
{
	return
		value_;
}

template<
	typename TypeEnum,
	typename Type
>
typename
alda::message::concrete<
	TypeEnum,
	Type
>::type_enum
alda::message::concrete<
	TypeEnum,
	Type
>::type() const
{
	return
		fcppt::cast::int_to_enum<
			type_enum
		>(
			alda::message::detail::extract_id<
				Type
			>::value
		);
}

template<
	typename TypeEnum,
	typename Type
>
alda::raw::buffer
alda::message::concrete<
	TypeEnum,
	Type
>::to_buffer() const
{
	return
		alda::raw::record_to_buffer(
			value_.get_base()
		);
}

template<
	typename TypeEnum,
	typename Type
>
typename
alda::message::concrete<
	TypeEnum,
	Type
>::unique_ptr
alda::message::concrete<
	TypeEnum,
	Type
>::clone() const
{
	return
		fcppt::unique_ptr_to_base<
			base_type
		>(
			fcppt::make_unique_ptr<
				concrete
			>(
				*this
			)
		);
}

#endif
