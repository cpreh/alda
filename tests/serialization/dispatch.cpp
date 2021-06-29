//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <alda/type_enum.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/call/object.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/init_record.hpp>
#include <alda/message/instantiate_base.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/object.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/define_context_function.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>
#include <alda/serialization/serialize.hpp>
#include <fcppt/text.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <bit>
#include <cstdint>
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

using
type_enum
=
alda::type_enum<
	message_type
>;

using
message_base
=
alda::message::base<
	type_enum
>;

using
message_base_unique_ptr
=
alda::message::base_unique_ptr<
	type_enum
>;

constexpr
std::endian const endianness{
	std::endian::little
};

using
uint16_type
=
alda::bindings::unsigned_<
	std::uint16_t,
	endianness
>;

using
uint32_type
=
alda::bindings::unsigned_<
	std::uint32_t,
	endianness
>;

FCPPT_RECORD_MAKE_LABEL(
	uint16_role
);

FCPPT_RECORD_MAKE_LABEL(
	uint32_role
);

using
message1
=
alda::message::object<
	alda::message::make_id<
		type_enum,
		message_type::message1
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			uint16_role,
			uint16_type
		>
	>
>;

using
message2
=
alda::message::object<
	alda::message::make_id<
		type_enum,
		message_type::message2
	>,
	alda::bindings::record_variadic<
		fcppt::record::element<
			uint32_role,
			uint32_type
		>
	>
>;

using
context
=
alda::serialization::context<
	type_enum
>;

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

/*
ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message2
);*/

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	type_enum,
	message2
);

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

namespace register1
{

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
ALDA_SERIALIZATION_REGISTER_MESSAGE(
	global_context(),
	type_enum,
	message1
);

}

namespace register2
{

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
ALDA_SERIALIZATION_REGISTER_MESSAGE(
	global_context(),
	type_enum,
	message2
);

}

FCPPT_PP_POP_WARNING

struct dispatcher_function
{
public:
	using
	result_type
	=
	void;

	void
	operator()(
		message1 const &_msg
	) const
	{
		CHECK(
			fcppt::record::get<
				uint16_role
			>(
				_msg.get()
			)
			==
			static_cast<
				std::uint16_t
			>(
				2//1337
			)
		);
	}

	void
	operator()(
		message2 const &_msg
	) const
	{
		CHECK(
			fcppt::record::get<
				uint32_role
			>(
				_msg.get()
			)
			==
			static_cast<
				std::uint32_t
			>(
				42
			)
		);
	}

	static
	result_type
	default_callback(
		message_base const &
	)
	{
		CHECK(
			false
		);
	}
};

}

TEST_CASE(
	"serialization dispatch",
	"[alda]"
)
{
	// NOLINTNEXTLINE(fuchsia-default-arguments-calls)
	std::ostringstream ofs{};

	alda::serialization::serialize(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			alda::message::init_record<
				message1
			>(
				uint16_role{} =
					static_cast<
						std::uint16_t
					>(
						2//1337
					)
			)
		)
	);

	// NOLINTNEXTLINE(fuchsia-default-arguments-calls)
	std::istringstream ifs{
		ofs.str()
	};

	using
	dispatcher
	=
	alda::call::object<
		type_enum,
		fcppt::mpl::list::object<
			message1,
			message2
		>,
		dispatcher_function
	>;

	dispatcher const dispatcher_object{};

	dispatcher_function receiver{};

	dispatcher::default_callback const default_callback(
		[](
			message_base const &_message
		){
			dispatcher_function::default_callback(
				_message
			);
		}
	);

	SECTION(
		"message1"
	)
	{
		message_base_unique_ptr result(
			alda::serialization::deserialize(
				global_context(),
				ifs
			)
		);

		CHECK(
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

	ofs.str("");

	alda::serialization::serialize(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			alda::message::init_record<
				message2
			>(
				uint32_role{} =
					static_cast<
						std::uint32_t
					>(
						42 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
					)
			)
		)
	);

	ifs.str(
		ofs.str()
	);

	SECTION(
		"message2"
	)
	{
		message_base_unique_ptr result(
			alda::serialization::deserialize(
				global_context(),
				ifs
			)
		);

		CHECK(
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
}
