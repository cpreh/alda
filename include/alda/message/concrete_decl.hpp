//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_CONCRETE_DECL_HPP_INCLUDED
#define ALDA_MESSAGE_CONCRETE_DECL_HPP_INCLUDED

#include <alda/detail/external_symbol.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/is_object.hpp>
#include <alda/message/object_decl.hpp>
#include <alda/raw/buffer_fwd.hpp>
#include <alda/raw/size_type.hpp>


namespace alda::message
{

template<
	typename TypeEnum,
	typename Type
>
class concrete
:
	public alda::message::base<
		TypeEnum
	>
{
	using
	base_type
	=
	alda::message::base<
		TypeEnum
	>;
public:
	using
	type_enum
	=
	typename
	base_type::type_enum;

	static_assert(
		alda::message::is_object<
			Type
		>::value,
		"Type is not an alda::message::object"
	);

	using
	object_type
	=
	Type;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	explicit
	concrete(
		Type
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	concrete(
		concrete const &
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	concrete &
	operator=(
		concrete const &
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	concrete(
		concrete &&
	)
	noexcept;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	concrete &
	operator=(
		concrete &&
	)
	noexcept;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	~concrete()
	override;

	[[nodiscard]]
	ALDA_DETAIL_EXTERNAL_SYMBOL
	Type const &
	value() const;
private:
	using
	unique_ptr
	=
	typename
	base_type::unique_ptr;

	[[nodiscard]]
	type_enum
	type() const
	override;

	[[nodiscard]]
	alda::raw::size_type
	size() const
	override;

	[[nodiscard]]
	alda::raw::buffer
	to_buffer() const
	override;

	[[nodiscard]]
	unique_ptr
	clone() const
	override;

	Type value_;
};

}

#endif
