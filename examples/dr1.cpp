#include <alda/bindings/array.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/static.hpp>
#include <alda/raw/get.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/record_variadic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char **argv
)
{
	typedef
	std::array<
		char,
		12
	>
	string;

	typedef
	std::array<
		std::uint16_t,
		16767
	>
	tile_array;

	typedef
	alda::bindings::array<
		string,
		alda::bindings::fundamental<
			char
		>
	>
	string_binding;

	typedef
	alda::bindings::unsigned_<
		std::uint16_t,
		fcppt::endianness::format::little
	>
	ui16le_binding;

	FCPPT_RECORD_MAKE_LABEL(
		actor_type_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		actor_pos_label
	);

	typedef
	fcppt::math::vector::static_<
		std::uint16_t,
		2
	>
	actor_pos;

	typedef
	alda::bindings::static_<
		actor_pos,
		ui16le_binding
	>
	actor_pos_binding;

	typedef
	alda::raw::record_variadic<
		fcppt::record::element<
			actor_type_label,
			ui16le_binding
		>,
		fcppt::record::element<
			actor_pos_label,
			actor_pos_binding
		>
	>
	actor_record;

	typedef
	std::vector<
		actor_record
	>
	actor_vector;

	struct actor_size_policy
	{
		static
		std::uint16_t
		make(
			std::uint16_t const _size
		)
		{
			return
				static_cast<
					std::uint16_t
				>(
					_size
					/
					3u
				);
		}
	};

	typedef
	alda::bindings::dynamic_len<
		actor_vector,
		actor_record,
		ui16le_binding,
		actor_size_policy
	>
	actor_binding;

	typedef
	alda::bindings::array<
		std::array<
			std::uint8_t,
			480
		>,
		alda::bindings::fundamental<
			std::uint8_t
		>
	>
	unknown_binding;

	typedef
	alda::bindings::array<
		tile_array,
		ui16le_binding
	>
	tile_array_binding;

	FCPPT_RECORD_MAKE_LABEL(
		mask_tiles_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		solid_tiles_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		backdrop_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		unused1_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		unused2_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		music_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		unused3_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		flags_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		width_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		actor_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		unknown_label
	);

	FCPPT_RECORD_MAKE_LABEL(
		tile_label
	);

	typedef
	alda::raw::record_variadic<
		fcppt::record::element<
			mask_tiles_label,
			string_binding
		>,
		fcppt::record::element<
			solid_tiles_label,
			string_binding
		>,
		fcppt::record::element<
			backdrop_label,
			string_binding
		>,
		fcppt::record::element<
			unused1_label,
			string_binding
		>,
		fcppt::record::element<
			unused2_label,
			string_binding
		>,
		fcppt::record::element<
			music_label,
			string_binding
		>,
		fcppt::record::element<
			unused3_label,
			string_binding
		>,
		fcppt::record::element<
			flags_label,
			ui16le_binding
		>,
		fcppt::record::element<
			width_label,
			ui16le_binding
		>,
		fcppt::record::element<
			actor_label,
			actor_binding
		>,
		fcppt::record::element<
			unknown_label,
			unknown_binding
		>,
		fcppt::record::element<
			tile_label,
			tile_array_binding
		>
	>
	level;

	if(
		argc
		!=
		2
	)
	{
		std::cerr
			<<
			"Usage: dr1 <filename>\n";

		return
			EXIT_FAILURE;
	}

	std::ifstream input(
		argv[1]
	);

	if(
		!input.is_open()
	)
	{
		std::cerr
			<<
			"Cannot open the specified file!\n";

		return
			EXIT_FAILURE;
	}

	fcppt::either::match(
		alda::raw::make_generic<
			alda::raw::stream::istream,
			level
		>(
			input
		),
		[](
			alda::raw::stream::error const &_error
		){
			fcppt::io::cerr()
				<<
				FCPPT_TEXT("Parsing failed: ")
				<<
				_error
				<<
				FCPPT_TEXT(".\n");
		},
		[](
			level &&_level
		)
		{
			std::cout
				<<
				"Success.\n";
			for(
				actor_record const &actor
				:
				alda::raw::get<
					actor_label
				>(
					_level
				)
			)
				std::cout
					<<
					"Actor type "
					<<
					alda::raw::get<
						actor_type_label
					>(
						actor
					)
					<<
					" at "
					<<
					alda::raw::get<
						actor_pos_label
					>(
						actor
					)
					<<
					'\n';
		}
	);

	return
		EXIT_SUCCESS;
}
