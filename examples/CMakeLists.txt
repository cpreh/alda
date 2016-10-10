include(
	CMakeParseArguments
)

function(
	add_alda_example
	FILE_NAME
)
	set(
		MULTI_ARGS
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
	)
endfunction()

add_alda_example(
	dr1
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)
