//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_NET_IO_SERVICE_WRAPPER_HPP_INCLUDED
#define ALDA_NET_IO_SERVICE_WRAPPER_HPP_INCLUDED

#include <alda/net/io_service_wrapper_fwd.hpp> // IWYU pragma: keep
#include <alda/net/detail/symbol.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_context.hpp>
#include <fcppt/config/external_end.hpp>

namespace alda::net
{

class io_service_wrapper
{
public:
  ALDA_NET_DETAIL_SYMBOL
  explicit io_service_wrapper(boost::asio::io_context &); // NOLINT(google-runtime-references)

  [[nodiscard]] ALDA_NET_DETAIL_SYMBOL boost::asio::io_context &get() const;

private:
  fcppt::reference<boost::asio::io_context> io_context_;
};

}

#endif
