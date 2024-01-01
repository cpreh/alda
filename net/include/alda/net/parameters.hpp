//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_PARAMETERS_HPP_INCLUDED
#define ALDA_NET_PARAMETERS_HPP_INCLUDED

#include <alda/net/io_service_wrapper_fwd.hpp>
#include <alda/net/parameters_fwd.hpp> // IWYU pragma: keep
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <alda/net/detail/symbol.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/context_reference.hpp>

namespace alda::net
{

class parameters
{
public:
  ALDA_NET_DETAIL_SYMBOL
  parameters(
      fcppt::log::context_reference,
      alda::net::io_service_wrapper const &,
      alda::net::buffer::max_send_size,
      alda::net::buffer::max_receive_size);

  [[nodiscard]] fcppt::log::context_reference log_context() const;

  [[nodiscard]] alda::net::io_service_wrapper const &io_service_wrapper() const;

  [[nodiscard]] alda::net::buffer::max_send_size max_send_size() const;

  [[nodiscard]] alda::net::buffer::max_receive_size max_receive_size() const;

private:
  fcppt::log::context_reference log_context_;

  fcppt::reference<alda::net::io_service_wrapper const> io_service_wrapper_;

  alda::net::buffer::max_send_size max_send_size_;

  alda::net::buffer::max_receive_size max_receive_size_;
};

}

#endif
