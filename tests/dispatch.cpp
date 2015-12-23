//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/exception.hpp>
#include <alda/type_enum_fcppt.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/call/object.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/instantiate_base.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/message/make_id.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/define_context_function.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>
#include <alda/serialization/serialize.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/text.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

enum class message_type
{
	message1,
	message2,
	fcppt_maximum = message2
};

typedef
alda::type_enum_fcppt<
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

constexpr
fcppt::endianness::format const endianness{
	fcppt::endianness::format::little
};

typedef
alda::bindings::fundamental<
	std::uint16_t,
	endianness
>
uint16_type;

typedef
alda::bindings::fundamental<
	std::uint32_t,
	endianness
>
uint32_type;

MAJUTSU_MAKE_ROLE_TAG(
	uint16_role
);

MAJUTSU_MAKE_ROLE_TAG(
	uint32_role
);

typedef
alda::message::make_class<
	boost::mpl::vector2<
		alda::message::make_id<
			type_enum,
			message_type::message1
		>,
		majutsu::role<
			uint16_type,
			uint16_role
		>
	>
>
message1;

typedef
alda::message::make_class<
	boost::mpl::vector2<
		alda::message::make_id<
			type_enum,
			message_type::message2
		>,
		majutsu::role<
			uint32_type,
			uint32_role
		>
	>
>
message2;

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

ALDA_MESSAGE_INSTANTIATE_BASE(
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_DETAILS(
	type_enum
);

ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message1
);

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	type_enum,
	message1
);

ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message2
);

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	type_enum,
	message2
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

namespace register2
{

ALDA_SERIALIZATION_REGISTER_MESSAGE(
	global_context(),
	type_enum,
	message2
);

}

struct dispatcher_function
{
public:
	typedef void result_type;

	result_type
	operator()(
		message1 const &_msg
	) const
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("message1 received\n");

		BOOST_CHECK_EQUAL(
			_msg.get<
				uint16_role
			>(),
			static_cast<
				std::uint16_t
			>(
				2//1337
			)
		);
	}

	result_type
	operator()(
		message2 const &_msg
	) const
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("message2 received\n");

		BOOST_CHECK_EQUAL(
			_msg.get<
				uint32_role
			>(),
			static_cast<
				std::uint32_t
			>(
				42
			)
		);
	}

	result_type
	default_callback(
		message_base const &
	)
	{
		BOOST_CHECK(
			false
		);
	}
};

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_dispatch
)
{
FCPPT_PP_POP_WARNING

	std::ostringstream ofs;

	alda::serialization::serialize(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			message1(
				uint16_role{} =
					static_cast<
						std::uint16_t
					>(
						2//1337
					)
			)
		)
	);

	std::istringstream ifs(
		ofs.str()
	);

	typedef alda::call::object<
		type_enum,
		boost::mpl::vector2<
			message1,
			message2
		>,
		dispatcher_function
	> dispatcher;

	dispatcher const dispatcher_object;

	dispatcher_function receiver;

	dispatcher::default_callback const default_callback(
		std::bind(
			&dispatcher_function::default_callback,
			&receiver,
			std::placeholders::_1
		)
	);

	try
	{
		message_base_unique_ptr result(
			alda::serialization::deserialize(
				global_context(),
				ifs
			)
		);

		BOOST_CHECK(
			result->type()
			==
			message_type::message1
		);

		dispatcher_object(
			*result,
			receiver,
			default_callback
		);
	}
	catch(
		alda::exception const &_exception
	)
	{
		fcppt::io::cerr()
			<< _exception.string()
			<< FCPPT_TEXT('\n');
	}

	ofs.str("");

	alda::serialization::serialize(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			message2(
				uint32_role{} =
					static_cast<
						std::uint32_t
					>(
						42
					)
			)
		)
	);

	ifs.str(
		ofs.str()
	);

	try
	{
		message_base_unique_ptr result(
			alda::serialization::deserialize(
				global_context(),
				ifs
			)
		);

		BOOST_CHECK(
			result->type()
			==
			message_type::message2
		);

		dispatcher_object(
			*result,
			receiver,
			default_callback
		);
	}
	catch(
		alda::exception const &_exception
	)
	{
		fcppt::io::cerr()
			<< _exception.string()
			<< FCPPT_TEXT('\n');
	}
}
