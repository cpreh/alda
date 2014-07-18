//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
