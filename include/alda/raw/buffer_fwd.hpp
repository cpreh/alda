//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_BUFFER_FWD_HPP_INCLUDED
#define ALDA_RAW_BUFFER_FWD_HPP_INCLUDED

#include <alda/raw/data.hpp>
#include <fcppt/container/raw_vector_fwd.hpp>


namespace alda
{
namespace raw
{

typedef
fcppt::container::raw_vector<
	alda::raw::data
>
buffer;

}
}

#endif
