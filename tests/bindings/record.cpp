#include <alda/bindings/bool.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/optional.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/raw/buffer.hpp>
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/is_static_size_v.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/needed_size.hpp>
#include <alda/raw/static_size.hpp>
#include <alda/raw/to_buffer.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/memory.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/either.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/record.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/strong_typedef.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>

namespace
{

using int_ = alda::bindings::fundamental<int>;

FCPPT_RECORD_MAKE_LABEL(int_role);

FCPPT_RECORD_MAKE_LABEL(record_role);

using inner_record_binding =
    alda::bindings::record_variadic<fcppt::record::element<int_role, int_>>;

static_assert(
    alda::raw::static_size<inner_record_binding>::value == // NOLINT(misc-redundant-expression)
    alda::raw::static_size<int_>::value);

using inner_record = alda::raw::element_type<inner_record_binding>;

using record_binding = alda::bindings::record_variadic<
    fcppt::record::element<int_role, int_>,
    fcppt::record::element<record_role, inner_record_binding>>;

static_assert(
    alda::raw::static_size<record_binding>::value ==
    alda::raw::static_size<inner_record_binding>::value + alda::raw::static_size<int_>::value);

FCPPT_RECORD_MAKE_LABEL(optional_label);

static_assert(
    !alda::raw::is_static_size_v<alda::bindings::record_variadic<
        fcppt::record::
            element<optional_label, alda::bindings::optional<bool, alda::bindings::bool_>>,
        fcppt::record::element<int_role, int_>>>);

using record = alda::raw::element_type<record_binding>;

using either_result_type = fcppt::either::object<alda::raw::stream::error, record>;

}

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("bindings::record istream", "[alda]")
{
  record const test{int_role{} = 42, record_role{} = inner_record{int_role{} = 10}};

  CHECK(
      alda::raw::needed_size<record_binding>(test) ==
      alda::raw::static_size<record_binding>::value);

  // NOLINTNEXTLINE(fuchsia-default-arguments-calls)
  std::stringstream stream{};

  alda::serialization::write<record_binding>(stream, test);

  CHECK(
      alda::serialization::read<record_binding>(stream) ==
      fcppt::either::make_success<alda::raw::stream::error>(test));

  CHECK(alda::serialization::read<record_binding>(stream).has_failure());
}

TEST_CASE("bindings::record raw", "[alda]")
{
  record const test{int_role{} = 42, record_role{} = inner_record{int_role{} = 10}};

  alda::raw::buffer const buffer(alda::raw::to_buffer<record_binding>(test));

  alda::raw::const_pointer stream(buffer.data());

  record const result{alda::raw::make_generic<alda::raw::stream::memory, record_binding>(stream)};

  CHECK(test == result);
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
