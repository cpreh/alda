cmake_minimum_required(
	VERSION
	2.8.12
)

project(
	alda
)

set_property(
	GLOBAL
	PROPERTY
	USE_FOLDERS
	ON
)

include(
	GNUInstallDirs
)

find_package(
	fcppt
	REQUIRED
)

find_package(
	Brigand
	REQUIRED
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

set(
	NEEDED_BOOST_LIBS
	"system"
)

option(
	ENABLE_TEST
	"Build the tests"
	ON
)

find_package(
	Boost 1.47.0
	REQUIRED
	COMPONENTS
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
	find_package(
		Catch2
		REQUIRED
	)

	fcppt_utils_setup_tests()

	enable_testing()

	add_subdirectory(
		tests
	)
endif()

fcppt_utils_generate_config(
	CONFIG_PATH
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}
)
