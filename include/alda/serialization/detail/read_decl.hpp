//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_DECL_HPP_INCLUDED

#include <alda/detail/external_symbol.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/tag_fwd.hpp>


namespace alda
{
namespace serialization
{
namespace detail
{

template<
	typename TypeEnum
>
class read
{
public:
	using
	message_unique_ptr
	=
	alda::message::base_unique_ptr<
		TypeEnum
	>;

	explicit
	read(
		alda::serialization::istream &
	);

	template<
		typename Message
	>
	ALDA_DETAIL_EXTERNAL_SYMBOL
	message_unique_ptr
	operator()(
		fcppt::tag<
			Message
		>
	) const;
private:
	fcppt::reference<
		alda::serialization::istream
	> stream_;
};

}
}
}

#endif
