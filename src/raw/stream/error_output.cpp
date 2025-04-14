#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/error_output.hpp>
#include <alda/raw/stream/int_error.hpp>
#include <alda/raw/stream/int_error_kind_to_string.hpp> // IWYU pragma: keep
#include <alda/raw/stream/stream_fail.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_index.hpp>
#include <fcppt/enum/to_string.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>

fcppt::io::ostream &
alda::raw::stream::operator<<(fcppt::io::ostream &_stream, alda::raw::stream::error const &_error)
{
  _stream << FCPPT_TEXT("Type ")
          << fcppt::from_std_string(fcppt::type_name_from_index(_error.type())) << FCPPT_TEXT(": ");

  fcppt::variant::match(
      _error.value(),
      [&_stream](alda::raw::stream::stream_fail)
      {
        _stream << FCPPT_TEXT("Stream failed.");
      },
      [&_stream](alda::raw::stream::int_error const &_int_error)
      {
        _stream << fcppt::from_std_string(fcppt::enum_::to_string(_int_error.kind()))
                << _int_error.value() << FCPPT_TEXT('.');
      });

  return _stream;
}
