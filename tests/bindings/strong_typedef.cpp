//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/strong_typedef.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
base_type;

FCPPT_MAKE_STRONG_TYPEDEF(
	base_type,
	strong_type
);

typedef
alda::bindings::strong_typedef<
	strong_type,
	alda::bindings::unsigned_<
		base_type,
		fcppt::endianness::format::little
	>
>
strong_binding;

FCPPT_RECORD_MAKE_LABEL(
	strong_role
);

typedef
alda::raw::record_variadic<
	fcppt::record::element<
		strong_role,
		strong_binding
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_enum
)
{
FCPPT_PP_POP_WARNING

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			strong_role
		>(
			message{
				strong_role{} =
					fcppt::strong_typedef_construct_cast<
						strong_type,
						fcppt::cast::size_fun
					>(
						42u
					)
			}
		).get(),
		42u
	);
}
