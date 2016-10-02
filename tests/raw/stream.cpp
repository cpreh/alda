#include <alda/bindings/fundamental.hpp>
#include <alda/raw/buffer.hpp>
#include <alda/raw/const_pointer.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/record_to_buffer.hpp>
#include <alda/raw/record_variadic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <alda/raw/stream/memory.hpp>
#include <alda/serialization/write_record.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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
alda::raw::record_variadic<
	fcppt::record::element<
		int_role,
		int_
	>
>
inner_record;

typedef
alda::raw::record_variadic<
	fcppt::record::element<
		int_role,
		int_
	>,
	fcppt::record::element<
		record_role,
		inner_record
	>
>
record;

typedef
fcppt::either::object<
	alda::raw::stream::error,
	record
>
optional_record;

}

BOOST_TEST_DONT_PRINT_LOG_VALUE(
	optional_record
)

BOOST_TEST_DONT_PRINT_LOG_VALUE(
	record
)

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

	alda::serialization::write_record(
		stream,
		test
	);

	optional_record const result{
		alda::raw::make_generic<
			alda::raw::stream::istream,
			record
		>(
			stream
		)
	};

	BOOST_CHECK_EQUAL(
		optional_record{
			test
		},
		result
	);

	optional_record const result2{
		alda::raw::make_generic<
			alda::raw::stream::istream,
			record
		>(
			stream
		)
	};

	BOOST_CHECK(
		result2.has_failure()
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
		alda::raw::record_to_buffer(
			test
		)
	);

	alda::raw::const_pointer stream(
		buffer.data()
	);

	record const result{
		alda::raw::make_generic<
			alda::raw::stream::memory,
			record
		>(
			stream
		)
	};

	BOOST_CHECK_EQUAL(
		test,
		result
	);
}
