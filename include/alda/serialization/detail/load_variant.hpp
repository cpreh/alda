//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_LOAD_VARIANT_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_LOAD_VARIANT_HPP_INCLUDED

#include <alda/bindings/variant_decl.hpp>
#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/mpl/index_of.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{

template<
	typename Types,
	typename AdaptedTypes
>
class load_variant
{
	FCPPT_NONASSIGNABLE(
		load_variant
	);
public:
	explicit
	load_variant(
		alda::serialization::istream &_is
	)
	:
		is_(
			_is
		)
	{
	}

	typedef
	typename
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>::type
	result_type;

	template<
		typename Type
	>
	result_type
	operator()() const
	{
		return
			result_type(
				alda::serialization::load<
					typename
					boost::mpl::at<
						AdaptedTypes,
						typename
						fcppt::mpl::index_of<
							Types,
							Type
						>::type
					>::type
				>::get(
					is_
				)
			);
	}
private:
	alda::serialization::istream &is_;
};

}
}
}

#endif
