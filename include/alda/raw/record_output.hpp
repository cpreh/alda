//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_OUTPUT_HPP_INCLUDED
#define ALDA_RAW_RECORD_OUTPUT_HPP_INCLUDED

#include <alda/raw/record_impl.hpp>
#include <majutsu/record_output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

template<
	typename Types
>
std::ostream &
operator<<(
	std::ostream &_stream,
	alda::raw::record<
		Types
	> const &_record
)
{
	return
		_stream
		<<
		_record.get_base();
}

}
}

#endif
