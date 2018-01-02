//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/exception.hpp>
#include <alda/type_enum.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/optional.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/variant.hpp>
#include <alda/call/friend_dispatcher.hpp>
#include <alda/call/object.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/init_record.hpp>
#include <alda/message/instantiate_base.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/optional_base_unique_ptr.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/define_context_function.hpp>
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>
#include <alda/serialization/length/deserialize.hpp>
#include <alda/serialization/length/put.hpp>
#include <alda/serialization/length/remaining_size_function.hpp>
#include <alda/serialization/length/serialize.hpp>
#include <fcppt/const.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/variant/equal.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{

enum class message_type
{
	message1,
	fcppt_maximum = message1
};

typedef
alda::type_enum<
	message_type
>
type_enum;

typedef
alda::message::base<
	type_enum
>
message_base;

typedef
alda::message::base_unique_ptr<
	type_enum
>
message_base_unique_ptr;

typedef
alda::message::optional_base_unique_ptr<
	type_enum
>
optional_message_base_unique_ptr;

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
alda::bindings::fundamental<
	std::uint16_t
>
uint16_type;

typedef
alda::bindings::optional<
	std::uint16_t,
	uint16_type
>
optional_uint16_type;

typedef
alda::bindings::variant<
	brigand::list<
		std::uint16_t
	>,
	brigand::list<
		uint16_type
	>
>
variant_type;

typedef
alda::bindings::fundamental<
	char
>
char_type;

typedef
alda::bindings::dynamic_len<
	std::string,
	char_type,
	alda::bindings::unsigned_<
		std::uint16_t,
		endianness
	>
>
string_type;

FCPPT_RECORD_MAKE_LABEL(
	uint16_role
);

FCPPT_RECORD_MAKE_LABEL(
	optional_uint16_role
);

FCPPT_RECORD_MAKE_LABEL(
	variant_role
);

FCPPT_RECORD_MAKE_LABEL(
	string_role
);

typedef
alda::message::object<
	alda::message::make_id<
		type_enum,
		message_type::message1
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			uint16_role,
			uint16_type
		>,
		fcppt::record::element<
			optional_uint16_role,
			optional_uint16_type
		>,
		fcppt::record::element<
			variant_role,
			variant_type
		>,
		fcppt::record::element<
			string_role,
			string_type
		>
	>
>
message1;

typedef
alda::serialization::context<
	type_enum
>
context;

context &
global_context();

ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(
	type_enum,
	global_context
)

}

/*
ALDA_MESSAGE_INSTANTIATE_BASE(
	type_enum
);*/

ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_DETAILS(
	type_enum
);

/*
ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message1
);*/

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	type_enum,
	message1
);

namespace
{

namespace register1
{

ALDA_SERIALIZATION_REGISTER_MESSAGE(
	global_context(),
	type_enum,
	message1
);

}

struct dispatcher_function
{
	FCPPT_NONASSIGNABLE(
		dispatcher_function
	);
public:
	explicit
	dispatcher_function(
		std::uint16_t const _value
	)
	:
		value_(
			_value
		)
	{
	}
private:
	ALDA_CALL_FRIEND_DISPATCHER;

	typedef void result_type;

	result_type
	operator()(
		message1 const &_msg
	) const
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("message1 received\n");

		BOOST_CHECK_EQUAL(
			fcppt::record::get<
				uint16_role
			>(
				_msg.get()
			),
			value_
		);

		BOOST_CHECK_EQUAL(
			fcppt::record::get<
				optional_uint16_role
			>(
				_msg.get()
			),
			alda::raw::element_type<
				optional_uint16_type
			>(
				value_
			)
		);

		BOOST_CHECK_EQUAL(
			fcppt::record::get<
				variant_role
			>(
				_msg.get()
			),
			alda::raw::element_type<
				variant_type
			>(
				value_
			)
		);

		BOOST_CHECK_EQUAL(
			fcppt::record::get<
				string_role
			>(
				_msg.get()
			),
			alda::raw::element_type<
				string_type
			>(
				fcppt::insert_to_std_string(
					value_
				)
			)
		);
	}

	std::uint16_t const value_;
};

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_length_stream
)
try
{
FCPPT_PP_POP_WARNING

	std::ostringstream ofs;

	unsigned const count(
		5u
	);

	typedef std::uint16_t length_type;

	for(
		unsigned const index
		:
		fcppt::make_int_range_count(
			count
		)
	)
	{
		auto const casted_index(
			fcppt::cast::size<
				std::uint16_t
			>(
				index
			)
		);

		alda::serialization::length::serialize<
			length_type
		>(
			ofs,
			*alda::message::make_concrete_ptr<
				type_enum
			>(
				alda::message::init_record<
					message1
				>(
					uint16_role{} =
						casted_index,
					optional_uint16_role{} =
						alda::raw::element_type<
							optional_uint16_type
						>(
							casted_index
						),
					variant_role{} =
						alda::raw::element_type<
							variant_type
						>(
							casted_index
						),
					string_role{} =
						fcppt::insert_to_std_string(
							casted_index
						)
				)
			)
		);
	}

	std::istringstream ifs;

	ifs.str(
		ofs.str()
	);

	alda::serialization::length::remaining_size_function const remaining_size{
		[
			&ifs
		]{
			return
				ifs.rdbuf()->in_avail();
		}
	};

	typedef
	alda::call::object<
		type_enum,
		brigand::list<
			message1
		>,
		dispatcher_function
	>
	dispatcher;

	dispatcher const dispatcher_object;

	for(
		unsigned const index
		:
		fcppt::make_int_range_count(
			count
		)
	)
	{
		optional_message_base_unique_ptr const result(
			alda::serialization::length::deserialize<
				length_type
			>(
				global_context(),
				ifs,
				remaining_size
			)
		);

		BOOST_CHECK(
			fcppt::optional::maybe(
				result,
				fcppt::const_(
					false
				),
				[
					index,
					&dispatcher_object
				](
					message_base_unique_ptr const &_ptr
				)
				{
					dispatcher_function fun(
						fcppt::cast::size<
							std::uint16_t
						>(
							index
						)
					);

					dispatcher_object(
						*_ptr,
						fun,
						dispatcher::default_callback{
							[](
								message_base const &
							)
							{
								BOOST_CHECK(
									false
								);
							}
						}
					);

					return
						true;
				}
			)
		);
	}

	BOOST_CHECK(
		ifs.good()
	);

	ifs.str("");

	{
		optional_message_base_unique_ptr const ptr(
			alda::serialization::length::deserialize<
				length_type
			>(
				global_context(),
				ifs,
				remaining_size
			)
		);

		BOOST_CHECK(
			!ptr.has_value()
		);
	}

	BOOST_CHECK(
		ifs.good()
	);

	ofs.str("");

	alda::serialization::length::put<
		type_enum,
		length_type
	>(
		ofs,
		100u
	);

	ifs.str(
		ofs.str()
	);

	{
		optional_message_base_unique_ptr const ptr(
			alda::serialization::length::deserialize<
				length_type
			>(
				global_context(),
				ifs,
				remaining_size
			)
		);

		BOOST_CHECK(
			!ptr.has_value()
		);
	}

	BOOST_CHECK(
		ifs.good()
	);
}
catch(
	alda::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	BOOST_CHECK(
		false
	);
}
