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


#ifndef ALDA_SERIALIZATION_CONTEXT_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_CONTEXT_DECL_HPP_INCLUDED

#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/detail/dispatch/map.hpp>
#include <alda/serialization/detail/dispatch/register_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	typedef typename alda::serialization::detail::dispatch::map<
		TypeEnum
	>::type dispatch_map;

	dispatch_map const &
	handlers() const;
private:
	dispatch_map handlers_;

	template<
		typename OtherTypeEnum,
		typename Message
	> friend class
	alda::serialization::detail::dispatch::register_;
};

}
}

#endif
