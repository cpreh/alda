//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_DETAIL_VARIANT_PLACE_HPP_INCLUDED
#define ALDA_BINDINGS_DETAIL_VARIANT_PLACE_HPP_INCLUDED

#include <majutsu/raw/place.hpp>
#include <majutsu/raw/pointer.hpp>
#include <fcppt/nonassignable.hpp>
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
class variant_place
{
	FCPPT_NONASSIGNABLE(
		variant_place
	);
public:
	explicit
	variant_place(
		majutsu::raw::pointer const _mem
	)
	:
		mem_(
			_mem
		)
	{
	}

	typedef
	void
	result_type;

	template<
		typename Type
	>
	result_type
	operator()(
		Type const &_type
	) const
	{
		majutsu::raw::place<
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
			_type,
			mem_
		);
	}
private:
	majutsu::raw::pointer const mem_;
};

}
}
}

#endif
