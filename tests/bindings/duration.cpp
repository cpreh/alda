//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/duration.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/record_variadic.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <ratio>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
alda::bindings::duration<
	alda::bindings::unsigned_<
		std::uint32_t,
		fcppt::endianness::format::little
	>,
	std::milli
>
duration;

FCPPT_RECORD_MAKE_LABEL(
	duration_label
);

typedef
alda::raw::record_variadic<
	fcppt::record::element<
		duration_label,
		duration
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_duration
)
{
FCPPT_PP_POP_WARNING

	typedef
	alda::raw::element_type<
		duration
	>
	duration_type;

	BOOST_CHECK(
		alda::raw::get<
			duration_label
		>(
			message{
				duration_label{} =
					duration_type(
						10u
					)
			}
		)
		==
		duration_type(
			10u
		)
	);
}
