//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED
#define ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED

#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/detail/extract_id.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>


namespace alda
{
namespace call
{
namespace detail
{

template<
	typename TypeEnum,
	typename Callee,
	typename InstanceArray
>
class make_instance
{
	FCPPT_NONASSIGNABLE(
		make_instance
	);
public:
	explicit
	make_instance(
		InstanceArray &_instances
	)
	:
		instances_(
			_instances
		)
	{
	}

	template<
		typename Message
	>
	void
	operator()() const
	{
		instances_[
			alda::message::detail::extract_id<
				typename Message::types
			>::type::value
		] =
			fcppt::make_unique_ptr<
				alda::call::detail::concrete<
					TypeEnum,
					Callee,
					Message
				>
			>();
	}
private:
	InstanceArray &instances_;
};

}
}
}

#endif
