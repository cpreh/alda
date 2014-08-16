#ifndef ALDA_CALL_FRIEND_DISPATCHER_HPP_INCLUDED
#define ALDA_CALL_FRIEND_DISPATCHER_HPP_INCLUDED

#include <alda/call/object_fwd.hpp>
#include <alda/call/detail/base_fwd.hpp>
#include <alda/call/detail/concrete_fwd.hpp>


#define ALDA_CALL_FRIEND_DISPATCHER \
template<\
	typename,\
	typename,\
	typename\
> \
friend class alda::call::detail::concrete; \
\
template<\
	typename,\
	typename\
> \
friend class alda::call::detail::base; \
\
template<\
	typename,\
	typename,\
	typename\
> \
friend class alda::call::object \

#endif
