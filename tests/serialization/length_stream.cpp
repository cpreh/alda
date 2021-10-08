//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

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
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <bit>
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

using type_enum = alda::type_enum<message_type>;

using message_base = alda::message::base<type_enum>;

using message_base_unique_ptr = alda::message::base_unique_ptr<type_enum>;

using optional_message_base_unique_ptr = alda::message::optional_base_unique_ptr<type_enum>;

constexpr std::endian const endianness{std::endian::little};

using uint16_type = alda::bindings::fundamental<std::uint16_t>;

using optional_uint16_type = alda::bindings::optional<std::uint16_t, uint16_type>;

using variant_type = alda::bindings::
    variant<fcppt::mpl::list::object<std::uint16_t>, fcppt::mpl::list::object<uint16_type>>;

using char_type = alda::bindings::fundamental<char>;

using string_type = alda::bindings::
    dynamic_len<std::string, char_type, alda::bindings::unsigned_<std::uint16_t, endianness>>;

FCPPT_RECORD_MAKE_LABEL(uint16_role);

FCPPT_RECORD_MAKE_LABEL(optional_uint16_role);

FCPPT_RECORD_MAKE_LABEL(variant_role);

FCPPT_RECORD_MAKE_LABEL(string_role);

using message1 = alda::message::object<
    alda::message::make_id<type_enum, message_type::message1>,
    alda::bindings::record_variadic<
        fcppt::record::element<uint16_role, uint16_type>,
        fcppt::record::element<optional_uint16_role, optional_uint16_type>,
        fcppt::record::element<variant_role, variant_type>,
        fcppt::record::element<string_role, string_type>>>;

using context = alda::serialization::context<type_enum>;

context &global_context();

ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(type_enum, global_context)

}

/*
ALDA_MESSAGE_INSTANTIATE_BASE(
	type_enum
);*/

ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(type_enum);

ALDA_SERIALIZATION_INSTANTIATE_DETAILS(type_enum);

/*
ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message1
);*/

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(type_enum, message1);

namespace
{

namespace register1
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
ALDA_SERIALIZATION_REGISTER_MESSAGE(global_context(), type_enum, message1);

FCPPT_PP_POP_WARNING

}

struct dispatcher_function
{
public:
  explicit dispatcher_function(std::uint16_t const _value) : value_(_value) {}

private:
  ALDA_CALL_FRIEND_DISPATCHER;

  using result_type = void;

  result_type operator()(message1 const &_msg) const
  {
    CHECK(fcppt::record::get<uint16_role>(_msg.get()) == value_);

    CHECK(
        fcppt::record::get<optional_uint16_role>(_msg.get()) ==
        alda::raw::element_type<optional_uint16_type>(value_));

    CHECK(
        fcppt::record::get<variant_role>(_msg.get()) ==
        alda::raw::element_type<variant_type>(value_));

    CHECK(
        fcppt::record::get<string_role>(_msg.get()) ==
        alda::raw::element_type<string_type>(fcppt::output_to_std_string(value_)));
  }

  std::uint16_t value_;
};

}

FCPPT_CATCH_BEGIN

TEST_CASE("serialization::length_stream", "[alda]")
{
  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::ostringstream ofs{};

  unsigned const count(5U);

  using length_type = std::uint16_t;

  for (unsigned const index : fcppt::make_int_range_count(count))
  {
    auto const casted_index(fcppt::cast::size<std::uint16_t>(index));

    alda::serialization::length::serialize<length_type>(
        ofs,
        *alda::message::make_concrete_ptr<type_enum>(alda::message::init_record<message1>(
            uint16_role{} = casted_index,
            optional_uint16_role{} = alda::raw::element_type<optional_uint16_type>(casted_index),
            variant_role{} = alda::raw::element_type<variant_type>(casted_index),
            string_role{} = fcppt::output_to_std_string(casted_index))));
  }

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::istringstream ifs{};

  ifs.str(ofs.str());

  alda::serialization::length::remaining_size_function const remaining_size{
      [&ifs] { return ifs.rdbuf()->in_avail(); }};

  using dispatcher =
      alda::call::object<type_enum, fcppt::mpl::list::object<message1>, dispatcher_function>;

  dispatcher const dispatcher_object;

  for (unsigned const index : fcppt::make_int_range_count(count))
  {
    optional_message_base_unique_ptr const result(
        alda::serialization::length::deserialize<length_type>(
            global_context(), ifs, remaining_size));

    CHECK(fcppt::optional::maybe(
        result,
        fcppt::const_(false),
        [index, &dispatcher_object](message_base_unique_ptr const &_ptr)
        {
          dispatcher_function fun(fcppt::cast::size<std::uint16_t>(index));

          dispatcher_object(
              *_ptr, fun, dispatcher::default_callback{[](message_base const &) { CHECK(false); }});

          return true;
        }));
  }

  CHECK(ifs.good());

  ifs.str("");

  {
    optional_message_base_unique_ptr const ptr(
        alda::serialization::length::deserialize<length_type>(
            global_context(), ifs, remaining_size));

    CHECK(!ptr.has_value());
  }

  CHECK(ifs.good());

  ofs.str("");

  alda::serialization::length::put<type_enum, length_type>(
      ofs,
      100U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );

  ifs.str(ofs.str());

  {
    optional_message_base_unique_ptr const ptr(
        alda::serialization::length::deserialize<length_type>(
            global_context(), ifs, remaining_size));

    CHECK(!ptr.has_value());
  }

  CHECK(ifs.good());
}

FCPPT_CATCH_END
