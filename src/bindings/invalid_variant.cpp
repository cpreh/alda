#include <alda/exception.hpp>
#include <alda/bindings/invalid_variant.hpp>
#include <fcppt/text.hpp>


alda::bindings::invalid_variant::invalid_variant()
:
	alda::exception(
		FCPPT_TEXT("Invalid variant index")
	)
{
}
