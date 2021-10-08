//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_LENGTH_REMAINING_SIZE_FUNCTION_HPP_INCLUDED
#define ALDA_SERIALIZATION_LENGTH_REMAINING_SIZE_FUNCTION_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>

namespace alda::serialization::length
{

using remaining_size_function = fcppt::function<std::streamsize()>;

}

#endif
