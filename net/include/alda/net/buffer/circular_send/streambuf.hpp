//          Copyright Carl Philipp Reh 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_STREAMBUF_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_STREAMBUF_HPP_INCLUDED

#include <alda/net/value_type.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <alda/net/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <ios>
#include <streambuf>
#include <fcppt/config/external_end.hpp>

namespace alda::net::buffer::circular_send
{

class streambuf : public std::streambuf
{
  FCPPT_NONMOVABLE(streambuf);

  using impl_type = boost::circular_buffer<alda::net::value_type>;

public:
  using size_type = impl_type::size_type;

  using const_array_range = impl_type::const_array_range;

  ALDA_NET_DETAIL_SYMBOL
  explicit streambuf(alda::net::buffer::max_send_size);

  ALDA_NET_DETAIL_SYMBOL
  ~streambuf() override;

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL size_type space_left() const;

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL const_array_range send_part() const;

  ALDA_NET_DETAIL_SYMBOL
  void bytes_sent(size_type);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL bool empty() const;

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL size_type capacity() const;

  ALDA_NET_DETAIL_SYMBOL
  void clear();

private:
  std::streamsize xsputn(char_type const *, std::streamsize) override;

  int_type overflow(int_type) override;

  impl_type impl_;
};

}

#endif
