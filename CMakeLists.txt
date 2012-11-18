cmake_minimum_required(
	VERSION 2.6
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

option(
	ENABLE_SHARED
	"Build alda as shared libraries"
	TRUE
)

option(
	ENABLE_STATIC
	"Build alda as as static libraries"
	FALSE
)

if(
	ENABLE_SHARED
)
	set(
		ALDA_DEFAULT_LINK_TARGET
		"alda"
	)
endif()

if(
	ENABLE_STATIC
)
	set(
		ALDA_DEFAULT_LINK_TARGET
		"alda_static"
	)
endif()

if(
	NOT ENABLE_SHARED AND NOT ENABLE_STATIC
)
	message(
		FATAL_ERROR
		"You disabled both STATIC and SHARED"
	)
endif()

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

include_directories(
	${CMAKE_BINARY_DIR}/include
)

find_package(
	fcppt
	REQUIRED
)

add_definitions(
	${fcppt_DEFINITIONS}
)

include_directories(
	${fcppt_INCLUDE_DIRS}
)


# TODO: Move majutsu out of sge!
find_package(
	sge
	REQUIRED
)

add_definitions(
	${sge_DEFINITIONS}
)

include_directories(
	${sge_INCLUDE_DIRS}
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

fcppt_utils_include_path(
	alda_INCLUDE_DIR
)

fcppt_utils_generate_config(
	alda
)

install(
	FILES
	${CMAKE_SOURCE_DIR}/CMakeModules/FindAlda.cmake
	DESTINATION
	${INSTALL_CMAKEMODULES_DIR}
)

install(
	EXPORT
	aldaTargets
	DESTINATION
	${INSTALL_CMAKECONFIG_DIR}
)
