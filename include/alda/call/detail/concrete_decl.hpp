//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_CONCRETE_DECL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_CONCRETE_DECL_HPP_INCLUDED

#include <alda/call/detail/base_decl.hpp>
#include <alda/call/detail/concrete_fwd.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace alda
{
namespace call
{
namespace detail
{

template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
class concrete
:
	public
	alda::call::detail::base<
		TypeEnum,
		Callee
	>
{
	FCPPT_NONMOVABLE(
		concrete
	);

	using
	base_type
	=
	alda::call::detail::base<
		TypeEnum,
		Callee
	>;
public:
	using
	message_type
	=
	typename
	base_type::message_type;

	concrete();

	~concrete()
	override;

	typename Callee::result_type
	call(
		Callee &,
		message_type const &
	) const
	override;
};

}
}
}

#endif
