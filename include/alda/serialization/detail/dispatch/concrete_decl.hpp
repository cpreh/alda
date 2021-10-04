//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_DECL_HPP_INCLUDED

#include <alda/detail/external_symbol.hpp>
#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <fcppt/nonmovable.hpp>


namespace alda::serialization::detail::dispatch
{

template<
	typename TypeEnum,
	typename Message
>
class concrete
:
	public alda::serialization::detail::dispatch::base<
		TypeEnum
	>
{
	FCPPT_NONMOVABLE(
		concrete
	);

	using
	base_type
	=
	alda::serialization::detail::dispatch::base<
		TypeEnum
	>;
public:
	ALDA_DETAIL_EXTERNAL_SYMBOL
	concrete();

	ALDA_DETAIL_EXTERNAL_SYMBOL
	~concrete()
	override;

	using
	message_unique_ptr
	=
	typename
	base_type::message_unique_ptr;

	using
	reader
	=
	typename
	base_type::reader;

	[[nodiscard]]
	ALDA_DETAIL_EXTERNAL_SYMBOL
	message_unique_ptr
	on_dispatch(
		reader const &
	) const
	override;
};

}

#endif
