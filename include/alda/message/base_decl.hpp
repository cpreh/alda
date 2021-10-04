//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_MESSAGE_BASE_DECL_HPP_INCLUDED
#define ALDA_MESSAGE_BASE_DECL_HPP_INCLUDED

#include <alda/detail/external_class_symbol.hpp>
#include <alda/detail/external_symbol.hpp>
#include <alda/message/base_fwd.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/raw/buffer_fwd.hpp>
#include <alda/raw/size_type.hpp>


namespace alda::message
{

template<
	typename TypeEnum
>
class ALDA_DETAIL_EXTERNAL_CLASS_SYMBOL base
{
protected:
	ALDA_DETAIL_EXTERNAL_SYMBOL
	base();

	ALDA_DETAIL_EXTERNAL_SYMBOL
	base(
		base const &
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	base &
	operator=(
		base const &
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	base(
		base &&
	)
	noexcept;

	ALDA_DETAIL_EXTERNAL_SYMBOL
	base &
	operator=(
		base &&
	)
	noexcept;
public:
	using
	type_enum
	=
	typename
	TypeEnum::type;

	using
	unique_ptr
	=
	typename
	alda::message::base_unique_ptr<
		TypeEnum
	>;

	virtual
	~base() = 0;

	[[nodiscard]]
	virtual
	type_enum
	type() const = 0;

	[[nodiscard]]
	virtual
	alda::raw::size_type
	size() const = 0;

	[[nodiscard]]
	virtual
	alda::raw::buffer
	to_buffer() const = 0;

	[[nodiscard]]
	virtual
	unique_ptr
	clone() const = 0;
};

}

#endif
