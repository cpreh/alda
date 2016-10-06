//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED

#include <alda/bindings/record_fwd.hpp>
#include <alda/raw/element_type_tpl.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/element_to_label_tpl.hpp>
#include <fcppt/record/element_to_type_tpl.hpp>
#include <fcppt/record/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Types
>
struct record
{
	typedef
	Types
	types;

	typedef
	fcppt::record::object<
		typename
		boost::mpl::transform<
			Types,
			fcppt::record::element<
				fcppt::record::element_to_label_tpl<
					boost::mpl::_1
				>,
				alda::raw::element_type_tpl<
					fcppt::record::element_to_type_tpl<
						boost::mpl::_1
					>
				>
			>
		>::type
	>
	element_type;
};

}
}

#endif
