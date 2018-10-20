//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_STREAM_FAILURE_HPP_INCLUDED
#define ALDA_RAW_STREAM_FAILURE_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/detail/class_symbol.hpp>
#include <alda/detail/symbol.hpp>
#include <alda/raw/stream/failure_fwd.hpp>
#include <fcppt/string.hpp>


namespace alda
{
namespace raw
{
namespace stream
{

class ALDA_DETAIL_CLASS_SYMBOL failure
:
	public alda::exception
{
public:
	ALDA_DETAIL_SYMBOL
	explicit
	failure(
		fcppt::string &&
	);

	ALDA_DETAIL_SYMBOL
	failure(
		failure &&
	);

	ALDA_DETAIL_SYMBOL
	failure(
		failure const &
	);

	ALDA_DETAIL_SYMBOL
	failure &
	operator=(
		failure &&
	);

	ALDA_DETAIL_SYMBOL
	failure &
	operator=(
		failure const &
	);

	ALDA_DETAIL_SYMBOL
	~failure() noexcept
	override;
};

}
}
}

#endif
