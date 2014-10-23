//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_DETAIL_EXTERNAL_SYMBOL_HPP_INCLUDED
#define ALDA_DETAIL_EXTERNAL_SYMBOL_HPP_INCLUDED

#if defined(ALDA_EXTERNAL_INSTANTIATION)
#	if defined(ALDA_EXTERNAL_STATIC_LINK)
#		define ALDA_DETAIL_EXTERNAL_SYMBOL
#	elif defined(alda_external_EXPORTS)
#		include <fcppt/symbol/export.hpp>
#		define ALDA_DETAIL_EXTERNAL_SYMBOL FCPPT_SYMBOL_EXPORT
#	else
#		include <fcppt/symbol/import.hpp>
#		define ALDA_DETAIL_EXTERNAL_SYMBOL FCPPT_SYMBOL_IMPORT
#	endif
#else
#	define ALDA_DETAIL_EXTERNAL_SYMBOL
#endif

#endif
