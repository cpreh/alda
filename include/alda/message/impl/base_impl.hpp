//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_IMPL_BASE_IMPL_HPP_INCLUDED
#define ALDA_MESSAGE_IMPL_BASE_IMPL_HPP_INCLUDED

#include <alda/message/base_decl.hpp>


template<
	typename TypeEnum
>
alda::message::base<
	TypeEnum
>::base()
= default;

template<
	typename TypeEnum
>
alda::message::base<
	TypeEnum
>::base(
	base const &
) = default;

template<
	typename TypeEnum
>
alda::message::base<
	TypeEnum
> &
alda::message::base<
	TypeEnum
>::operator=(
	base const &
) = default;

template<
	typename TypeEnum
>
alda::message::base<
	TypeEnum
>::base(
	base &&
) noexcept
= default;

template<
	typename TypeEnum
>
alda::message::base<
	TypeEnum
> &
alda::message::base<
	TypeEnum
>::operator=(
	base &&
) noexcept
= default;

template<
	typename TypeEnum
>
alda::message::base<
	TypeEnum
>::~base<
	TypeEnum
>()
= default;

#endif
