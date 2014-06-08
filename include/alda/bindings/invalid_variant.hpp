#ifndef ALDA_BINDINGS_INVALID_VARIANT_HPP_INCLUDED
#define ALDA_BINDINGS_INVALID_VARIANT_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/detail/class_symbol.hpp>
#include <alda/detail/symbol.hpp>


namespace alda
{
namespace bindings
{

class ALDA_DETAIL_CLASS_SYMBOL invalid_variant
:
	public alda::exception
{
public:
	ALDA_DETAIL_SYMBOL
	invalid_variant();
};

}
}

#endif
