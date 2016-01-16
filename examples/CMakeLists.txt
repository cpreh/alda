include(
	CMakeParseArguments
)

function(
	add_alda_example
	FILE_NAME
)
	set(
		EXAMPLE_NAME
		alda_example_${FILE_NAME}
	)

	add_executable(
		${EXAMPLE_NAME}
		${FILE_NAME}.cpp
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

	fcppt_utils_set_target_compiler_flags(
		${EXAMPLE_NAME}
	)

	target_link_libraries(
		${EXAMPLE_NAME}
		PRIVATE
		${_LINK_LIBS}
	)
endfunction()

add_alda_example(
	dr1
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)
