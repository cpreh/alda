//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/exception.hpp>
#include <alda/raw/stream/failure.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

alda::raw::stream::failure::failure(fcppt::string &&_text)
    : alda::exception{FCPPT_TEXT("Stream failure: ") + std::move(_text)}
{
}

alda::raw::stream::failure::failure(failure &&) noexcept = default;

alda::raw::stream::failure::failure(failure const &) = default;

alda::raw::stream::failure &alda::raw::stream::failure::operator=(failure &&) noexcept = default;

alda::raw::stream::failure &alda::raw::stream::failure::operator=(failure const &) = default;

alda::raw::stream::failure::~failure() noexcept = default;
