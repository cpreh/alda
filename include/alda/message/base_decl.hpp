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
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/size_type.hpp>


namespace alda
{
namespace message
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
	);

	ALDA_DETAIL_EXTERNAL_SYMBOL
	base &
	operator=(
		base &&
	);
public:
	typedef
	typename
	TypeEnum::type
	type_enum;

	typedef
	majutsu::raw::const_pointer
	const_raw_pointer;

	typedef
	majutsu::raw::size_type
	size_type;

	typedef
	typename
	alda::message::base_unique_ptr<
		TypeEnum
	>
	unique_ptr;

	virtual
	~base() = 0;

	virtual
	type_enum
	type() const = 0;

	virtual
	const_raw_pointer
	data() const = 0;

	virtual
	size_type
	size() const = 0;

	virtual
	unique_ptr
	clone() const = 0;
};

}
}

#endif
