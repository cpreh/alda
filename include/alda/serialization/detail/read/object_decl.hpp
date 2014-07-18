//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_OBJECT_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_OBJECT_DECL_HPP_INCLUDED

#include <alda/detail/external_symbol.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{
namespace read
{

template<
	typename TypeEnum
>
class object
{
	FCPPT_NONASSIGNABLE(
		object
	);
public:
	typedef alda::message::base_unique_ptr<
		TypeEnum
	> message_unique_ptr;

	explicit
	object(
		alda::serialization::istream &
	);

	template<
		typename Message
	>
	ALDA_DETAIL_EXTERNAL_SYMBOL
	message_unique_ptr
	operator()() const;
private:
	alda::serialization::istream &stream_;
};

}
}
}
}

#endif
