//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_INIT_RECORD_HPP_INCLUDED
#define ALDA_MESSAGE_INIT_RECORD_HPP_INCLUDED

#include <alda/message/element_type.hpp>
#include <alda/message/is_object.hpp>
#include <fcppt/record/is_object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace alda::message
{

template<
	typename Object,
	typename... Args
>
inline
Object
init_record(
	Args &&... _args
)
{
	static_assert(
		alda::message::is_object<
			Object
		>::value,
		"Object must be a message::object"
	);

	static_assert(
		fcppt::record::is_object<
			alda::message::element_type<
				Object
			>
		>::value,
		"Object's element_type must be a record!"
	);

	return
		Object{
			alda::message::element_type<
				Object
			>{
				std::forward<
					Args
				>(
					_args
				)...
			}
		};
}

}

#endif
