//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED

#include <alda/bindings/record_fwd.hpp>
#include <alda/raw/element_type.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/element_to_label.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/from_list_fwd.hpp>


namespace alda::bindings
{

template<
	typename Types
>
struct record
{
	using
	types
	=
	Types;

	using
	element_type
	=
	fcppt::record::from_list<
		fcppt::mpl::list::map<
			Types,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					fcppt::record::element
				>,
				fcppt::mpl::lambda<
					fcppt::record::element_to_label
				>,
				fcppt::mpl::bind<
					fcppt::mpl::lambda<
						alda::raw::element_type
					>,
					fcppt::mpl::lambda<
						fcppt::record::element_to_type
					>
				>
			>
		>
	>;
};

}

#endif
