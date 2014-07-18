//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_NET_BUFFER_CIRCULAR_SEND_SINK_HPP_INCLUDED
#define ALDA_NET_BUFFER_CIRCULAR_SEND_SINK_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_send/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/concepts.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace net
{
namespace buffer
{
namespace circular_send
{

class sink
{
	FCPPT_NONASSIGNABLE(
		sink
	);
public:
	typedef alda::net::value_type
	char_type;

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	struct category
	:
		boost::iostreams::output,
		boost::iostreams::device_tag
	{
	};

	FCPPT_PP_POP_WARNING

	ALDA_DETAIL_SYMBOL
	explicit
	sink(
		alda::net::buffer::circular_send::object &
	);

	ALDA_DETAIL_SYMBOL
	std::streamsize
	write(
		char const *,
		std::streamsize
	);
private:
	alda::net::buffer::circular_send::object &container_;
};

}
}
}
}

#endif
