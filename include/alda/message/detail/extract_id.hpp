//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_MESSAGE_DETAIL_EXTRACT_ID_HPP_INCLUDED
#define ALDA_MESSAGE_DETAIL_EXTRACT_ID_HPP_INCLUDED

#include <alda/message/detail/extract_id_tpl.hpp>

namespace alda::message::detail
{

template <typename Message>
using extract_id = typename alda::message::detail::extract_id_tpl<Message>::type;

}

#endif
