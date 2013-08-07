#ifndef ALDA_BINDINGS_DYNAMIC_LEN_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_DECL_HPP_INCLUDED

#include <alda/bindings/dynamic_len_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct dynamic_len
{
	typedef Type type;

	typedef std::uint16_t length_type;
};

}
}

#endif
