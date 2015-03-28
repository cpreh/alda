include(
	CMakeParseArguments
)

function(
	ADD_ALDA_TEST
	TESTNAME
)
	set(
		MULTI_ARGS
		ADDITIONAL_DEPS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	fcppt_utils_add_test(
		${TESTNAME}
		LINK_LIBS
			${alda_TARGET}
			${_ADDITIONAL_DEPS}
	)
endfunction()

add_alda_test(
	bitfield
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	duration
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	dynamic_len
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	enum
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	enum_array
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	float
)

add_alda_test(
	length_stream
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	optional
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	signed
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	simple
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	static
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	strong_typedef
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_alda_test(
	variant
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)
