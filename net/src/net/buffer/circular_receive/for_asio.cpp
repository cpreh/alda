//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/net/buffer/circular_receive/for_asio.hpp>
#include <alda/net/buffer/circular_receive/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

boost::asio::mutable_buffers_1 alda::net::buffer::circular_receive::for_asio(
    alda::net::buffer::circular_receive::part const &_part)
{
  return {
      _part.begin(),
      std::min(
          _part.size(),
          fcppt::literal<alda::net::buffer::circular_receive::part::size_type>(
              4096U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ))};
}
