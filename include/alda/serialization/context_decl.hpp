//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_CONTEXT_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_CONTEXT_DECL_HPP_INCLUDED

#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/detail/dispatch/map.hpp>
#include <alda/serialization/detail/dispatch/register_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
class context
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	context();

	~context();

	using
	dispatch_map
	=
	alda::serialization::detail::dispatch::map<
		TypeEnum
	>;

	dispatch_map const &
	handlers() const;
private:
	dispatch_map handlers_;

	template<
		typename OtherTypeEnum,
		typename Message
	> friend class
	alda::serialization::detail::dispatch::register_;
};

}
}

#endif
