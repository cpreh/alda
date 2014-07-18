#ifndef ALDA_BINDINGS_DURATION_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_DURATION_DECL_HPP_INCLUDED

#include <alda/bindings/duration_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Adapted,
	typename Ratio
>
struct duration
{
	typedef
	std::chrono::duration<
		typename
		Adapted::type,
		Ratio
	>
	type;
};

}
}

#endif
