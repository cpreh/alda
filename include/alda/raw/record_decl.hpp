//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_RAW_RECORD_DECL_HPP_INCLUDED
#define ALDA_RAW_RECORD_DECL_HPP_INCLUDED

#include <alda/raw/record_fwd.hpp>
#include <alda/raw/detail/inner_types.hpp>
#include <majutsu/record_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace raw
{

template<
	typename Types
>
class record
:
	private
		majutsu::record<
			alda::raw::detail::inner_types<
				Types
			>
		>
{
public:
	static_assert(
		boost::mpl::is_sequence<
			Types
		>::value,
		"Types must be an MPL sequence"
	);

	typedef
	alda::raw::record<
		Types
	>
	element_type;

	typedef
	Types
	types;

	typedef
	majutsu::record<
		alda::raw::detail::inner_types<
			Types
		>
	>
	base;

	typedef
	typename
	base::all_types
	all_types;

	record(
		record &&
	);

	record(
		record &
	);

	record(
		record const &
	);

	record &
	operator=(
		record &&
	);

	record &
	operator=(
		record const &
	);

	~record();

	using
	base::base;

	using
	base::set;

	using
	base::get;
};

}
}

#endif
