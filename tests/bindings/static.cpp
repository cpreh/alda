//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/static.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
fcppt::math::vector::static_<
	unsigned,
	2
>
int_vec2;

typedef
alda::bindings::static_<
	int_vec2,
	alda::bindings::unsigned_<
		int_vec2::value_type,
		fcppt::endianness::format::little
	>
>
vector_binding;

FCPPT_RECORD_MAKE_LABEL(
	vector_role
);

typedef
alda::raw::record_variadic<
	fcppt::record::element<
		vector_role,
		vector_binding
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_static
)
{
FCPPT_PP_POP_WARNING

	int_vec2 const test(
		2u,
		5u
	);

	BOOST_CHECK_EQUAL(
		alda::raw::get<
			vector_role
		>(
			message{
				vector_role{} =
					test
			}
		),
		test
	);
}
