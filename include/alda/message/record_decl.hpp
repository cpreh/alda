//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_RECORD_DECL_HPP_INCLUDED
#define ALDA_MESSAGE_RECORD_DECL_HPP_INCLUDED

#include <alda/message/record_fwd.hpp>
#include <alda/raw/record_decl.hpp>


namespace alda
{
namespace message
{

// TODO: Why do we need this?
template<
	typename Id,
	typename Types
>
class record
:
	private
		alda::raw::record<
			Types
		>
{
public:
	typedef
	Id
	id_type;

	typedef
	alda::raw::record<
		Types
	>
	base_type;

	typedef
	typename
	base_type::all_types
	all_types;

	explicit
	record(
		base_type &&
	);

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
	base_type::base_type;

	using
	base_type::set;

	using
	base_type::get;

	base_type const &
	get_base() const;
};

}
}

#endif
