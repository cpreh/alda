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


namespace alda
{
namespace message
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
	typedef
	alda::message::base<
		TypeEnum
	>
	base_type;
public:
	typedef
	typename
	base_type::type_enum
	type_enum;

	static_assert(
		alda::message::is_object<
			Type
		>::value,
		"Type is not an alda::message::object"
	);

	typedef
	Type
	object_type;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	explicit
	concrete(
		Type &&
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	explicit
	concrete(
		Type const &
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
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	concrete &
	operator=(
		concrete &&
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	~concrete()
	override;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	Type const &
	value() const;
private:
	typedef
	typename
	base_type::unique_ptr
	unique_ptr;

	type_enum
	type() const
	override;

	alda::raw::size_type
	size() const
	override;

	alda::raw::buffer
	to_buffer() const
	override;

	unique_ptr
	clone() const
	override;

	Type value_;
};

}
}

#endif
