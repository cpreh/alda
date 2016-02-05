function(
	ADD_ALDA_TEST
	TESTNAME
)
	fcppt_utils_add_test(
		${TESTNAME}
		${ARGN}
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
)

add_alda_test(
	bindings/optional
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
	bindings/variant
	LINK_LIBS
		${fcppt_core_TARGET}
)

add_alda_test(
	message/record
)

add_alda_test(
	net/buffer/circular_receive
	LINK_LIBS
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

add_alda_test(
	raw/nested
)

add_alda_test(
	raw/record
)

add_alda_test(
	raw/stream
	LINK_LIBS
		${fcppt_core_TARGET}
)
