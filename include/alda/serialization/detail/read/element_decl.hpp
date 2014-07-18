//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_DETAIL_READ_ELEMENT_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_ELEMENT_DECL_HPP_INCLUDED

#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read/element_fwd.hpp>
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
	typename Class
>
class element
{
	FCPPT_NONASSIGNABLE(
		element
	);
public:
	element(
		alda::serialization::istream &,
		Class &
	);

	template<
		typename Role
	>
	void
	operator()(
		Role const &
	) const;
private:
	alda::serialization::istream &stream_;

	Class &object_;
};

}
}
}
}

#endif
