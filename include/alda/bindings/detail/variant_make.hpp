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


#ifndef ALDA_BINDINGS_DETAIL_VARIANT_MAKE_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_VARIANT_MAKE_HPP_INCLUDED

#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/mpl/index_of.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{
namespace detail
{

template<
	typename Types,
	typename AdaptedTypes
>
class variant_make
{
	FCPPT_NONASSIGNABLE(
		variant_make
	);
public:
	explicit
	variant_make(
		majutsu::const_raw_pointer const _mem
	)
	:
		mem_(
			_mem
		)
	{
	}

	typedef
	fcppt::variant::object<
		Types
	>
	result_type;

	template<
		typename Type
	>
	result_type
	operator()() const
	{
		return
			result_type(
				majutsu::make<
					typename
					boost::mpl::at<
						AdaptedTypes,
						typename
						fcppt::mpl::index_of<
							Types,
							Type
						>::type
					>::type
				>(
					mem_
				)
			);
	}
private:
	majutsu::const_raw_pointer const mem_;
};

}
}
}

#endif