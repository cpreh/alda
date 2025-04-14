#ifndef ALDA_RAW_STREAM_STREAM_FAIL_HPP_INCLUDED
#define ALDA_RAW_STREAM_STREAM_FAIL_HPP_INCLUDED

#include <alda/raw/stream/stream_fail_fwd.hpp> // IWYU pragma: export

namespace alda::raw::stream
{
struct stream_fail
{
  [[nodiscard]] bool operator==(stream_fail const &) const = default;
};
}

#endif
