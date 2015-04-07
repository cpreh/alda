//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/type_enum_fcppt.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/call/friend_dispatcher.hpp>
#include <alda/call/object.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/instantiate_base.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/optional_base_unique_ptr.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/define_context_function.hpp>
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>
#include <alda/serialization/length/deserialize.hpp>
#include <alda/serialization/length/put.hpp>
#include <alda/serialization/length/serialize.hpp>
#include <alda/serialization/load/static_size.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
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

enum class message_type
{
	message1,
	fcppt_maximum = message1
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

typedef
alda::message::optional_base_unique_ptr<
	type_enum
>
optional_message_base_unique_ptr;

typedef
alda::bindings::fundamental<
	std::uint16_t
>
uint16_type;

MAJUTSU_MAKE_ROLE_TAG(
	uint16_role
);

typedef
alda::message::make_class<
	majutsu::composite<
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

		BOOST_CHECK(
			_msg.get<
				uint16_role
			>()
			==
			value_
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
		alda::serialization::length::serialize<
			length_type
		>(
			ofs,
			*alda::message::make_concrete_ptr<
				type_enum
			>(
				message1(
					uint16_role{} =
						static_cast<
							std::uint16_t
						>(
							index
						)
				)
			)
		);

	std::istringstream ifs;

	ifs.str(
		ofs.str()
	);

	typedef alda::call::object<
		type_enum,
		boost::mpl::vector1<
			message1
		>,
		dispatcher_function
	> dispatcher;

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
				ifs
			)
		);

		BOOST_CHECK(
			fcppt::maybe(
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
						static_cast<
							std::uint16_t
						>(
							index
						)
					);

					dispatcher_object(
						*_ptr,
						fun,
						dispatcher::default_callback()
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
				ifs
			)
		);

		BOOST_CHECK(
			!ptr
		);
	}

	BOOST_CHECK(
		ifs.good()
	);

	ofs.str("");

	alda::serialization::length::put<
		length_type
	>(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			message1(
				uint16_role{} =
					static_cast<
						std::uint16_t
					>(
						0
					)
			)
		)
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
				ifs
			)
		);

		BOOST_CHECK(
			!ptr
		);
	}

	BOOST_CHECK(
		ifs.good()
	);
}
