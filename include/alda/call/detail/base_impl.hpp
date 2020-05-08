//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_BASE_IMPL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_BASE_IMPL_HPP_INCLUDED

#include <alda/call/detail/base_decl.hpp>


template<
	typename TypeEnum,
	typename Callee
>
alda::call::detail::base<
	TypeEnum,
	Callee
>::base()
= default;

template<
	typename TypeEnum,
	typename Callee
>
alda::call::detail::base<
	TypeEnum,
	Callee
>::~base()
= default;

#endif
