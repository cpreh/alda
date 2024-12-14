//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/net/io_service_wrapper.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_context.hpp>
#include <fcppt/config/external_end.hpp>

alda::net::io_service_wrapper::io_service_wrapper(boost::asio::io_context &_io_context)
    : io_context_{_io_context}
{
}

boost::asio::io_context &alda::net::io_service_wrapper::get() const
{
  return this->io_context_.get();
}
