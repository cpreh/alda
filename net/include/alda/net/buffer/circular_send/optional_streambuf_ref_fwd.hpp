//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_OPTIONAL_STREAMBUF_REF_FWD_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_OPTIONAL_STREAMBUF_REF_FWD_HPP_INCLUDED

#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace alda::net::buffer::circular_send
{

using optional_streambuf_ref =
    fcppt::optional::reference<alda::net::buffer::circular_send::streambuf>;

}

#endif
