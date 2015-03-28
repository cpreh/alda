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

include_directories(
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/include
)

include_directories(
	${FCPPT_UTILS_PROJECT_BINARY_DIR}/include
)

find_package(
	fcppt
	REQUIRED
)

find_package(
	majutsu
	REQUIRED
)

include_directories(
	${majutsu_INCLUDE_DIRS}
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

include_directories(
	${FCPPT_UTILS_INCLUDE_SYSTEM}
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

add_subdirectory(
	src
)

if(
	ENABLE_TEST
)
	enable_testing()

	add_subdirectory(
		tests
	)
endif()

fcppt_utils_generate_config(
	TRUE
)
