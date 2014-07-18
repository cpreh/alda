//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_BASE_DECL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_BASE_DECL_HPP_INCLUDED

#include <alda/call/detail/base_fwd.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace call
{
namespace detail
{

template<
	typename TypeEnum,
	typename Callee
>
class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	typedef alda::message::base<
		TypeEnum
	> message_type;

	virtual typename Callee::result_type
	call(
		Callee &,
		message_type const &
	) const = 0;
};

}
}
}

#endif
