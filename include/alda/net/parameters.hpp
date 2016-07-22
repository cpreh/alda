//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_PARAMETERS_HPP_INCLUDED
#define ALDA_NET_PARAMETERS_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/io_service_wrapper_fwd.hpp>
#include <alda/net/parameters_fwd.hpp>
#include <alda/net/buffer/max_receive_size.hpp>
#include <alda/net/buffer/max_send_size.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace alda
{
namespace net
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	ALDA_DETAIL_SYMBOL
	parameters(
		fcppt::log::context &,
		alda::net::io_service_wrapper const &,
		alda::net::buffer::max_send_size,
		alda::net::buffer::max_receive_size
	);

	fcppt::log::context &
	log_context() const;

	alda::net::io_service_wrapper const &
	io_service_wrapper() const;

	alda::net::buffer::max_send_size
	max_send_size() const;

	alda::net::buffer::max_receive_size
	max_receive_size() const;
private:
	fcppt::log::context &log_context_;

	alda::net::io_service_wrapper const &io_service_wrapper_;

	alda::net::buffer::max_send_size const max_send_size_;

	alda::net::buffer::max_receive_size const max_receive_size_;
};

}
}

#endif
