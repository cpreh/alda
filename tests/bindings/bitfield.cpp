//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/bitfield.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/integral_size.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/container/bitfield/comparison.hpp>
#include <fcppt/container/bitfield/object.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_bitfield
)
{
FCPPT_PP_POP_WARNING

	typedef
	fcppt::container::bitfield::object<
		unsigned,
		alda::raw::integral_size<
			64u
		>
	>
	bitfield;

	typedef
	alda::bindings::bitfield<
		bitfield,
		fcppt::endianness::format::little
	>
	bitfield_binding;

	FCPPT_RECORD_MAKE_LABEL(
		bitfield_label
	);

	typedef
	alda::raw::record_variadic<
		fcppt::record::element<
			bitfield_label,
			bitfield_binding
		>
	>
	message;

	bitfield test(
		bitfield::null()
	);

	test[
		42u
	] = true;

	BOOST_CHECK(
		alda::raw::get<
			bitfield_label
		>(
			message{
				bitfield_label{} =
					test
			}
		)
		==
		test
	);
}
