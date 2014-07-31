//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_CALL_OBJECT_DECL_HPP_INCLUDED
#define ALDA_CALL_OBJECT_DECL_HPP_INCLUDED

#include <alda/call/default_callback.hpp>
#include <alda/call/object_fwd.hpp>
#include <alda/call/detail/base_fwd.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace call
{

template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);

	typedef typename Callee::result_type result_type;

	typedef alda::call::detail::base<
		TypeEnum,
		Callee
	> base;
public:
	typedef alda::call::default_callback<
		TypeEnum,
		result_type
	> default_callback;

	typedef alda::message::base<
		TypeEnum
	> message_base;

	object();

	~object();

	result_type
	operator()(
		message_base const &,
		Callee &,
		default_callback const &
	) const;
private:
	typedef
	std::array<
		std::unique_ptr<
			base
		>,
		static_cast<
			std::size_t
		>(
			TypeEnum::size::value
		)
	>
	instance_array;

	instance_array instances_;
};

}
}

#endif
