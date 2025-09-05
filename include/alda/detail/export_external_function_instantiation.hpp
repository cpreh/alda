//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION_HPP_INCLUDED
#define ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION_HPP_INCLUDED

#ifdef ALDA_EXTERNAL_INSTANTIATION
#ifdef ALDA_EXTERNAL_STATIC_LINK
#define ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION
#else
#include <fcppt/symbol/export_function_instantiation.hpp>
#define ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION \
  FCPPT_SYMBOL_EXPORT_FUNCTION_INSTANTIATION
#endif
#else
#define ALDA_DETAIL_EXPORT_EXTERNAL_FUNCTION_INSTANTIATION
#endif

#endif
