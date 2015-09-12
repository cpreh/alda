//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_IMPL_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_MESSAGE_IMPL_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/message/concrete_decl.hpp>
#include <alda/message/detail/extract_id.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


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
	return value_;
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
	TypeEnum,
	Type
>::type_enum
alda::message::concrete<
	TypeEnum,
	Type
>::type() const
{
	return
		static_cast<
			type_enum
		>(
			alda::message::detail::extract_id<
				typename Type::types
			>::value
		);
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
	TypeEnum,
	Type
>::const_raw_pointer
alda::message::concrete<
	TypeEnum,
	Type
>::data() const
{
	return
		value_.data();
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
	TypeEnum,
	Type
>::size_type
alda::message::concrete<
	TypeEnum,
	Type
>::size() const
{
	return
		value_.size();
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
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
