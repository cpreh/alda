#include <alda/bindings/array.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/bindings/static.hpp>
#include <majutsu/make_role_tag.hpp>
#include <majutsu/role.hpp>
#include <majutsu/raw/make_generic.hpp>
#include <majutsu/raw/record_variadic.hpp>
#include <majutsu/raw/stream/istream.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/optional/maybe.hpp>
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
			char,
			fcppt::endianness::format::little
		>
	>
	string_binding;

	typedef
	alda::bindings::fundamental<
		std::uint16_t,
		fcppt::endianness::format::little
	>
	ui16le_binding;

	MAJUTSU_MAKE_ROLE_TAG(
		actor_type_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		actor_pos_role
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
	majutsu::raw::record_variadic<
		majutsu::role<
			ui16le_binding,
			actor_type_role
		>,
		majutsu::role<
			actor_pos_binding,
			actor_pos_role
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
		place(
			actor_vector const &_actors
		)
		{
			return
				fcppt::cast::size<
					std::uint16_t
				>(
					_actors.size()
					*
					3u
				);
		}

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
			std::uint8_t,
			fcppt::endianness::format::little
		>
	>
	unknown_binding;

	typedef
	alda::bindings::array<
		tile_array,
		ui16le_binding
	>
	tile_array_binding;

	MAJUTSU_MAKE_ROLE_TAG(
		mask_tiles_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		solid_tiles_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		backdrop_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		unused1_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		unused2_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		music_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		unused3_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		flags_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		width_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		actor_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		unknown_role
	);

	MAJUTSU_MAKE_ROLE_TAG(
		tile_role
	);

	typedef
	majutsu::raw::record_variadic<
		majutsu::role<
			string_binding,
			mask_tiles_role
		>,
		majutsu::role<
			string_binding,
			solid_tiles_role
		>,
		majutsu::role<
			string_binding,
			backdrop_role
		>,
		majutsu::role<
			string_binding,
			unused1_role
		>,
		majutsu::role<
			string_binding,
			unused2_role
		>,
		majutsu::role<
			string_binding,
			music_role
		>,
		majutsu::role<
			string_binding,
			unused3_role
		>,
		majutsu::role<
			ui16le_binding,
			flags_role
		>,
		majutsu::role<
			ui16le_binding,
			width_role
		>,
		majutsu::role<
			actor_binding,
			actor_role
		>,
		majutsu::role<
			unknown_binding,
			unknown_role
		>,
		majutsu::role<
			tile_array_binding,
			tile_role
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

	fcppt::optional::maybe(
		majutsu::raw::make_generic<
			majutsu::raw::stream::istream,
			level
		>(
			input
		),
		[]{
			std::cerr
				<<
				"Parsing failed.\n";
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
				majutsu::get<
					actor_role
				>(
					_level
				)
			)
				std::cout
					<<
					"Actor type "
					<<
					majutsu::get<
						actor_type_role
					>(
						actor
					)
					<<
					" at "
					<<
					majutsu::get<
						actor_pos_role
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
