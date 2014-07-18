//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_DETAIL_EXTRACT_ID_HPP_INCLUDED
#define ALDA_MESSAGE_DETAIL_EXTRACT_ID_HPP_INCLUDED

#include <alda/message/roles/type.hpp>
#include <majutsu/extract_constant.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace message
{
namespace detail
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Message
>
struct extract_id
:
majutsu::extract_constant<
	Message,
	alda::message::roles::type
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
