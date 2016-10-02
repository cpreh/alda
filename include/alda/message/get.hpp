//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_GET_HPP_INCLUDED
#define ALDA_MESSAGE_GET_HPP_INCLUDED

#include <alda/message/record_impl.hpp>
#include <fcppt/record/label_value_type.hpp>


namespace alda
{
namespace message
{

// TODO: This is really ugly
template<
	typename Label,
	typename Id,
	typename Types
>
fcppt::record::label_value_type<
	typename
	alda::message::record<
		Id,
		Types
	>::base_type::base,
	Label
>
get(
	alda::message::record<
		Id,
		Types
	> const &_arg
)
{
	return
		_arg. template get<
			Label
		>();
}

}
}

#endif
