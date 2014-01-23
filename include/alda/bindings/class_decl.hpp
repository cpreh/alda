#ifndef ALDA_BINDINGS_CLASS_DECL_HPP_INCLUDED
#define ALDA_BINDINGS_CLASS_DECL_HPP_INCLUDED

#include <alda/bindings/class_fwd.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

// TODO: Make a special version for staticically sized classes
template<
	typename Type
>
struct class_
:
alda::bindings::dynamic_len<
	Type,
	Type
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
