include(
	CMakeParseArguments
)

function(
	ADD_ALDA_TEST
	TESTNAME
)
	set(
		OPTION_ARGS
		NO_CODE
	)

	set(
		MULTI_ARGS
		LINK_LIBS
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	if(
		_NO_CODE
	)
		set(
			NO_CODE
			NO_CODE
		)
	endif()

	fcppt_utils_add_test(
		${TESTNAME}
		${NO_CODE}
		LINK_LIBS
			alda_interface
			${_LINK_LIBS}
	)
endfunction()

add_alda_test(
	smallest_uint
	NO_CODE
)

add_alda_test(
	bindings/array
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/bitfield
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/duration
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/dynamic_len
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/enum
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/enum_array
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/float
	LINK_LIBS
		${alda_TARGET}
)

add_alda_test(
	bindings/optional
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/record
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/signed
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)

add_alda_test(
	bindings/static
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/strong_typedef
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	bindings/unit
)

add_alda_test(
	bindings/variant
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)

add_alda_test(
	net/buffer/circular_receive/streambuf
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)

add_alda_test(
	serialization/dispatch
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)

add_alda_test(
	serialization/length_stream
	LINK_LIBS
		${fcppt_core_TARGET}
		${alda_TARGET}
)

add_alda_test(
	raw/combine_static_sizes
	NO_CODE
)
