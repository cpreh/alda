//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_BASE_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_BASE_IMPL_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/base_decl.hpp>


template<
	typename TypeEnum
>
alda::serialization::detail::dispatch::base<
	TypeEnum
>::base()
= default;

template<
	typename TypeEnum
>
alda::serialization::detail::dispatch::base<
	TypeEnum
>::~base<
	TypeEnum
>()
= default;

#endif
