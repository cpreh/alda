//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_OPTIONAL_BASE_UNIQUE_PTR_FWD_HPP_INCLUDED
#define ALDA_MESSAGE_OPTIONAL_BASE_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace alda::message
{

template<
	typename TypeEnum
>
using optional_base_unique_ptr
=
fcppt::optional::object<
	alda::message::base_unique_ptr<
		TypeEnum
	>
>;

}

#endif
