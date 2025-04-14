#ifndef ALDA_RAW_STREAM_ERROR_OUTPUT_HPP_INCLUDED
#define ALDA_RAW_STREAM_ERROR_OUTPUT_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/raw/stream/error_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>

namespace alda::raw::stream
{
ALDA_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, alda::raw::stream::error const &);
}

#endif
