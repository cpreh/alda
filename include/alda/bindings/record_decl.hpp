//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_DECL_HPP_INCLUDED

#include <alda/bindings/record_fwd.hpp>
#include <alda/raw/element_type.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/record/element_to_label.hpp>
#include <fcppt/record/element_to_type.hpp>
#include <fcppt/record/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/list/transform.hpp>
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
		metal::transform<
			metal::bind<
				metal::lambda<
					fcppt::record::element
				>,
				metal::lambda<
					fcppt::record::element_to_label
				>,
				metal::bind<
					metal::lambda<
						alda::raw::element_type
					>,
					metal::lambda<
						fcppt::record::element_to_type
					>
				>
			>,
			Types
		>
	>
	element_type;
};

}
}

#endif
