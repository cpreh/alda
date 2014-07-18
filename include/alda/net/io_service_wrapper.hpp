//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_IO_SERVICE_WRAPPER_HPP_INCLUDED
#define ALDA_NET_IO_SERVICE_WRAPPER_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{

class io_service_wrapper
{
	FCPPT_NONASSIGNABLE(
		io_service_wrapper
	);
public:
	ALDA_DETAIL_SYMBOL
	explicit
	io_service_wrapper(
		boost::asio::io_service &
	);

	ALDA_DETAIL_SYMBOL
	boost::asio::io_service &
	get() const;
private:
	boost::asio::io_service &io_service_;
};

}
}

#endif
