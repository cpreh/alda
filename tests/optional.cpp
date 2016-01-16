//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/optional.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/get.hpp>
#include <majutsu/role.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/write.hpp>
#include <majutsu/raw/stream/istream.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::uint32_t
base_type;

typedef
fcppt::optional::object<
	base_type
>
optional_type;

typedef
alda::bindings::optional<
	base_type,
	alda::bindings::unsigned_<
		base_type,
		fcppt::endianness::format::little
	>
>
optional_binding;

MAJUTSU_MAKE_ROLE_TAG(
	optional_role
);

typedef
alda::message::make_class<
	boost::mpl::vector1<
		majutsu::role<
			optional_binding,
			optional_role
		>
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_optional
)
{
FCPPT_PP_POP_WARNING
	BOOST_CHECK_EQUAL(
		message(
			optional_role{} =
				optional_type()
		).get<
			optional_role
		>(),
		optional_type()
	);

	message const msg(
		optional_role{} =
			optional_type(
				42u
			)
	);

	BOOST_CHECK_EQUAL(
		msg.get<
			optional_role
		>(),
		optional_type(
			42u
		)
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_optional_stream
)
{
FCPPT_PP_POP_WARNING

	std::stringstream stream;

	majutsu::raw::write(
		stream,
		message(
			optional_role{} =
				optional_type(
					42u
				)
		)
	);

	typedef
	fcppt::optional::object<
		message
	>
	optional_message;

	optional_message const result(
		majutsu::raw::make_generic<
			majutsu::raw::stream::istream,
			message
		>(
			stream
		)
	);

	BOOST_REQUIRE(
		result.has_value()
	);

	BOOST_CHECK_EQUAL(
		majutsu::get<
			optional_role
		>(
			result.get_unsafe()
		),
		optional_type(
			42u
		)
	);
}
