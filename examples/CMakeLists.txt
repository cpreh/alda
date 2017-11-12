include(
	CMakeParseArguments
)

function(
	add_alda_example
	FILE_NAME
)
	set(
		MULTI_ARGS
		COMPILE_OPTIONS
		LINK_LIBS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	fcppt_utils_add_example(
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/examples
		${FILE_NAME}
		LINK_LIBS
			${_LINK_LIBS}
		COMPILE_OPTIONS
			${_COMPILE_OPTIONS}
	)
endfunction()

add_alda_example(
	dr1
	COMPILE_OPTIONS
		${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
	LINK_LIBS
		${Boost_FILESYSTEM_LIBRARIES}
		${fcppt_core_TARGET}
		${fcppt_filesystem_TARGET}
		${fcppt_options_TARGET}
		${FCPPT_UTILS_MAIN_LINK_LIBS}
		${alda_TARGET}
)
