#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/raw/buffer.hpp>
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/to_buffer.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/memory.hpp>
#include <alda/serialization/read.hpp>
#include <alda/serialization/write.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/either/output.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/comparison.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
alda::bindings::fundamental<
	int
>
int_;

FCPPT_RECORD_MAKE_LABEL(
	int_role
);

FCPPT_RECORD_MAKE_LABEL(
	record_role
);

typedef
alda::bindings::record_variadic<
	fcppt::record::element<
		int_role,
		int_
	>
>
inner_record_binding;

typedef
alda::raw::element_type<
	inner_record_binding
>
inner_record;

typedef
alda::bindings::record_variadic<
	fcppt::record::element<
		int_role,
		int_
	>,
	fcppt::record::element<
		record_role,
		inner_record_binding
	>
>
record_binding;

typedef
alda::raw::element_type<
	record_binding
>
record;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	record
>
either_result_type;

}

#if !defined(FCPPT_NARROW_STRING)
BOOST_TEST_DONT_PRINT_LOG_VALUE(
	either_result_type
)
#endif


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	raw_stream_istream
)
{
FCPPT_PP_POP_WARNING

	record const test{
		int_role{} = 42,
		record_role{} =
			inner_record{
				int_role{} = 10
			}
	};

	std::stringstream stream;

	alda::serialization::write<
		record_binding
	>(
		stream,
		test
	);

	BOOST_CHECK_EQUAL(
		alda::serialization::read<
			record_binding
		>(
			stream
		),
		fcppt::either::make_success<
			alda::raw::stream::error
		>(
			test
		)
	);

	BOOST_CHECK(
		alda::serialization::read<
			record_binding
		>(
			stream
		).has_failure()
	);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	raw_stream_memory
)
{
FCPPT_PP_POP_WARNING

	record const test{
		int_role{} = 42,
		record_role{} =
			inner_record{
				int_role{} = 10
			}
	};

	alda::raw::buffer const buffer(
		alda::raw::to_buffer<
			record_binding
		>(
			test
		)
	);

	alda::raw::const_pointer stream(
		buffer.data()
	);

	record const result{
		alda::raw::make_generic<
			alda::raw::stream::memory,
			record_binding
		>(
			stream
		)
	};

	BOOST_CHECK_EQUAL(
		test,
		result
	);
}
