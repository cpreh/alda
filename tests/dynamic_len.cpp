//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/get.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/write.hpp>
#include <majutsu/raw/stream/istream.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
alda::bindings::unsigned_<
	std::uint16_t,
	endianness
>
length_binding;

typedef
alda::bindings::fundamental<
	unsigned,
	endianness
>
uint_binding;

typedef
std::vector<
	unsigned
>
uint_vector;

typedef
alda::bindings::dynamic_len<
	uint_vector,
	uint_binding,
	length_binding
>
dynamic_len_binding;

MAJUTSU_MAKE_ROLE_TAG(
	dynamic_len_role
);

typedef
alda::message::make_class<
	boost::mpl::vector1<
		majutsu::role<
			dynamic_len_binding,
			dynamic_len_role
		>
	>
>
message;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_dynamic_len
)
{
FCPPT_PP_POP_WARNING

	uint_vector const vec{
		1,
		2
	};

	uint_vector const result(
		message(
			dynamic_len_role{} =
				vec
		).get<
			dynamic_len_role
		>()
	);

	auto const output(
		[](
			uint_vector const &_vec
		){
			std::clog << '(';

			for(
				auto const &elem
				:
				_vec
			)
				std::clog << elem << ',';

			std::clog << ')';
		}
	);

	output(
		vec
	);

	std::clog << "==";

	output(
		result
	);

	std::clog << "\n";

	BOOST_CHECK(
		vec
		==
		result
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_dynamic_len_stream
)
{
FCPPT_PP_POP_WARNING

	uint_vector const vec{
		1,
		2
	};

	std::stringstream stream;

	majutsu::raw::write(
		stream,
		message{
			dynamic_len_role{} =
				vec
		}
	);

	typedef
	fcppt::optional::object<
		message
	>
	optional_result;

	optional_result const result(
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

	BOOST_CHECK(
		majutsu::get<
			dynamic_len_role
		>(
			result.get_unsafe()
		)
		==
		vec
	);
}
