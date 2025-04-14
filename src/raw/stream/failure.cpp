//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/exception.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/error_output.hpp> // IWYU pragma: keep
#include <alda/raw/stream/failure.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>

alda::raw::stream::failure::failure(alda::raw::stream::error const _error)
    : alda::exception{FCPPT_TEXT("Stream failure: ") + fcppt::output_to_fcppt_string(_error)},
      error_{_error}
{
}

alda::raw::stream::failure::failure(failure &&) noexcept = default;

alda::raw::stream::failure::failure(failure const &) = default;

alda::raw::stream::failure &alda::raw::stream::failure::operator=(failure &&) noexcept = default;

alda::raw::stream::failure &alda::raw::stream::failure::operator=(failure const &) = default;

alda::raw::stream::failure::~failure() noexcept = default;

alda::raw::stream::error const &alda::raw::stream::failure::get() const { return this->error_; }
