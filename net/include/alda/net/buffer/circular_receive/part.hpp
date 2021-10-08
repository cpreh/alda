//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_BUFFER_CIRCULAR_RECEIVE_PART_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_RECEIVE_PART_HPP_INCLUDED

#include <alda/net/size_type.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/part_fwd.hpp>
#include <alda/net/detail/symbol.hpp>

namespace alda::net::buffer::circular_receive
{

class part
{
public:
  using pointer = alda::net::value_type *;

  using size_type = alda::net::size_type;

  ALDA_NET_DETAIL_SYMBOL
  part(pointer begin, pointer end);

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL pointer begin() const;

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL pointer end() const;

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL size_type size() const;

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL bool empty() const;

private:
  pointer begin_;

  pointer end_;
};

}

#endif
