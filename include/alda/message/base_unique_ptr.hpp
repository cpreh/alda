//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_BASE_UNIQUE_PTR_HPP_INCLUDED
#define ALDA_MESSAGE_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <alda/message/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace message
{

template<
	typename TypeEnum
>
using base_unique_ptr
=
std::unique_ptr<
	alda::message::base<
		TypeEnum
	>
>;

}
}

#endif
