//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_DECL_HPP_INCLUDED

#include <alda/detail/external_symbol.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/detail/dispatch/register_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace dispatch
{

template<
	typename TypeEnum,
	typename Message
>
class register_
{
	FCPPT_NONCOPYABLE(
		register_
	);
public:
	typedef alda::serialization::context<
		TypeEnum
	> context;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	explicit
	register_(
		context &
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	~register_();
};

}
}
}
}

#endif
