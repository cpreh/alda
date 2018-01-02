//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_DETAIL_APPLY_BINARY_HPP_INCLUDED
#define ALDA_RAW_DETAIL_APPLY_BINARY_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{
namespace detail
{


// TODO: How do we express this using brigand alone?
template<
	typename Function,
	typename Size1,
	typename Size2
>
struct apply_binary
:
brigand::apply<
	Function,
	Size1,
	Size2
>
{
};

}
}
}

#endif
