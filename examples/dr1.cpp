#include <alda/bindings/array.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/bindings/unsigned.hpp>
#include <alda/bindings/static.hpp>
#include <alda/raw/element_type.hpp>
#include <alda/raw/make_generic.hpp>
#include <alda/raw/stream/error.hpp>
#include <alda/raw/stream/istream.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <ios>
#include <iostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

int
parse_file(
	std::istream &_stream
)
{
	typedef
	alda::bindings::array<
		std::array<
			char,
			12
		>,
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
	alda::bindings::record_variadic<
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
		alda::raw::element_type<
			actor_record
		>
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
		std::array<
			std::uint16_t,
			16767
		>,
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
	alda::bindings::record_variadic<
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

	return
		fcppt::either::match(
			alda::raw::make_generic<
				alda::raw::stream::istream,
				level
			>(
				_stream
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

				return
					EXIT_FAILURE;
			},
			[](
				alda::raw::element_type<
					level
				> &&_level
			)
			{
				std::cout
					<<
					"Success.\n";

				for(
					alda::raw::element_type<
						actor_record
					> const &actor
					:
					fcppt::record::get<
						actor_label
					>(
						_level
					)
				)
					std::cout
						<<
						"Actor type "
						<<
						fcppt::record::get<
							actor_type_label
						>(
							actor
						)
						<<
						" at "
						<<
						fcppt::record::get<
							actor_pos_label
						>(
							actor
						)
						<<
						'\n';

				return
					EXIT_SUCCESS;
			}
		);
}

FCPPT_RECORD_MAKE_LABEL(
	path_label
);

}

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
{
	auto const parser(
		fcppt::options::argument<
			path_label,
			fcppt::string
		>{
			fcppt::options::long_name{
				FCPPT_TEXT("filename")
			},
			fcppt::options::optional_help_text{}
		}
	);

	return
		fcppt::either::match(
			fcppt::options::parse(
				parser,
				fcppt::args_from_second(
					argc,
					argv
				)
			),
			[](
				fcppt::options::error const &_error
			)
			{
				fcppt::io::cerr()
					<<
					_error
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_FAILURE;
			},
			[](
				fcppt::options::result_of<
					decltype(
						parser
					)
				> const &_args
			)
			{
				boost::filesystem::path const path{
					fcppt::record::get<
						path_label
					>(
						_args
					)
				};

				return
					fcppt::optional::maybe(
						fcppt::filesystem::open<
							std::ifstream
						>(
							path,
							std::ios_base::in
							|
							std::ios_base::binary
						),
						[
							&path
						]{
							fcppt::io::cerr()
								<<
								FCPPT_TEXT("Unable to open ")
								<<
								fcppt::filesystem::path_to_string(
									path
								)
								<<
								FCPPT_TEXT('\n');

							return
								EXIT_FAILURE;
						},
						[](
							std::ifstream &&_stream
						)
						{
							return
								parse_file(
									_stream
								);
						}
					);
			}
		);
}
