#ifndef ALDA_RAW_STREAM_INT_ERROR_HPP_INCLUDED
#define ALDA_RAW_STREAM_INT_ERROR_HPP_INCLUDED

#include <alda/detail/symbol.hpp>
#include <alda/raw/stream/int_error_fwd.hpp> // IWYU pragma: export
#include <alda/raw/stream/int_error_kind.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace alda::raw::stream
{
class int_error
{
public:
  using type = std::uintmax_t;

  ALDA_DETAIL_SYMBOL int_error(alda::raw::stream::int_error_kind, type);

  [[nodiscard]] ALDA_DETAIL_SYMBOL alda::raw::stream::int_error_kind kind() const;

  [[nodiscard]] ALDA_DETAIL_SYMBOL type value() const;

  [[nodiscard]] ALDA_DETAIL_SYMBOL bool operator==(int_error const &) const;
private:
  alda::raw::stream::int_error_kind kind_;
  type value_;
};
}

#endif
