/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef ALDA_CALL_DETAIL_CONCRETE_DECL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_CONCRETE_DECL_HPP_INCLUDED

#include <alda/call/detail/base_decl.hpp>
#include <alda/call/detail/concrete_fwd.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace call
{
namespace detail
{

template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
class concrete
:
	public alda::call::detail::base<
		TypeEnum,
		Callee
	>
{
	FCPPT_NONCOPYABLE(
		concrete
	);

	typedef alda::call::detail::base<
		TypeEnum,
		Callee
	> base_type;
public:
	typedef typename base_type::message_type message_type;

	concrete();

	~concrete();

	typename Callee::result_type
	call(
		Callee &,
		message_type const &
	) const;
};

}
}
}

#endif
