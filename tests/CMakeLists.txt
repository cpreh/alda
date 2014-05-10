function(
	ADD_ALDA_TEST
	TESTNAME
	ADDITIONAL_LIBRARIES
)
	fcppt_utils_add_test(
		${TESTNAME}
		"${ALDA_DEFAULT_LINK_TARGET};${ADDITIONAL_LIBRARIES}"
		""
	)
endfunction()

add_alda_test(
	bitfield
	"${fcppt_core_TARGET}"
)

add_alda_test(
	dynamic_len
	"${fcppt_core_TARGET}"
)

add_alda_test(
	enum
	"${fcppt_core_TARGET}"
)

add_alda_test(
	float
	""
)

add_alda_test(
	length_stream
	"${fcppt_core_TARGET}"
)

add_alda_test(
	optional
	"${fcppt_core_TARGET}"
)

add_alda_test(
	signed
	"${fcppt_core_TARGET}"
)

add_alda_test(
	simple
	"${fcppt_core_TARGET}"
)

add_alda_test(
	static
	"${fcppt_core_TARGET}"
)

add_alda_test(
	strong_typedef
	"${fcppt_core_TARGET}"
)

add_alda_test(
	variant
	"${fcppt_core_TARGET}"
)
