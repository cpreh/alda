//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <alda/exception.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

alda::exception::exception(fcppt::string &&_message) : fcppt::exception(std::move(_message)) {}

alda::exception::exception(exception &&) noexcept = default;

alda::exception::exception(exception const &) = default;

alda::exception &alda::exception::operator=(exception &&) noexcept = default;

alda::exception &alda::exception::operator=(exception const &) = default;

alda::exception::~exception() noexcept = default;
