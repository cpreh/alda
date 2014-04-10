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


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_BASE_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_BASE_DECL_HPP_INCLUDED

#include <alda/detail/external_class_symbol.hpp>
#include <alda/detail/external_symbol.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/detail/dispatch/base_fwd.hpp>
#include <alda/serialization/detail/read/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace dispatch
{

template<
	typename TypeEnum
>
class ALDA_DETAIL_EXTERNAL_CLASS_SYMBOL base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	ALDA_DETAIL_EXTERNAL_SYMBOL
	base();
public:
	typedef alda::message::base_unique_ptr<
		TypeEnum
	> message_unique_ptr;

	typedef alda::serialization::detail::read::object<
		TypeEnum
	> reader;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	virtual
	~base() = 0;

	virtual
	message_unique_ptr
	on_dispatch(
		reader const &
	) const = 0;
};

}
}
}
}

#endif
