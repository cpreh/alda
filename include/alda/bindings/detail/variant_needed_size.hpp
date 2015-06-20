//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DETAIL_VARIANT_NEEDED_SIZE_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_VARIANT_NEEDED_SIZE_HPP_INCLUDED

#include <majutsu/raw/needed_size.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/mpl/index_of.hpp>
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
struct variant_needed_size
{
	typedef
	majutsu::raw::size_type
	result_type;

	template<
		typename Type
	>
	result_type
	operator()(
		Type const &_type
	) const
	{
		return
			majutsu::raw::needed_size<
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
				_type
			);
	}
};

}
}
}

#endif
