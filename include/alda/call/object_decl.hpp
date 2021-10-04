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
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace alda::call
{

template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
class object
{
	FCPPT_NONMOVABLE(
		object
	);

	using
	result_type
	=
	typename Callee::result_type;

	using
	base
	=
	alda::call::detail::base<
		TypeEnum,
		Callee
	>;
public:
	using
	default_callback
	=
	alda::call::default_callback<
		TypeEnum,
		result_type
	>;
	using
	message_base
	=
	alda::message::base<
		TypeEnum
	>;

	object();

	~object();

	result_type
	operator()(
		message_base const &,
		Callee &,
		default_callback const &
	) const;
private:
	using
	base_unique_ptr
	=
	fcppt::unique_ptr<
		base
	>;

	using
	optional_base_unique_ptr
	=
	fcppt::optional::object<
		base_unique_ptr
	>;

	using
	instance_array
	=
	fcppt::enum_::array<
		typename
		TypeEnum::type,
		optional_base_unique_ptr
	>;

	instance_array const instances_;
};

}

#endif
