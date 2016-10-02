cmake_minimum_required(
	VERSION 2.8.12
)

project(
	alda
)

include(
	FcpptCMakeUtils
)

include(
	FcpptSymbol
)

fcppt_utils_static_shared()

fcppt_utils_link_target(
	alda
)

find_package(
	fcppt
	REQUIRED
)

set(
	NEEDED_BOOST_LIBS
	"system"
)

option(
	ENABLE_TEST
	"Build the tests"
	ON
)

if(
	ENABLE_TEST
)
	list(
		APPEND
		NEEDED_BOOST_LIBS
		"unit_test_framework"
	)
endif()

find_package(
	Boost 1.47.0 REQUIRED COMPONENTS
	${NEEDED_BOOST_LIBS}
)

add_subdirectory(
	src
)

option(
	ENABLE_EXAMPLES
	"Build the examples"
	ON
)

if(
	ENABLE_EXAMPLES
)
	add_subdirectory(
		examples
	)
endif()

if(
	ENABLE_TEST
)
	enable_testing()

	add_subdirectory(
		tests
	)
endif()

fcppt_utils_generate_config()
