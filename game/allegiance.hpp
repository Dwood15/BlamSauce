/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "../cseries/MacrosCpp.h"
#include "../cseries/base.h"

namespace Yelo {
	namespace Enums {
		enum game_team : short {
			_game_team_none = -10,

			_game_team_default = 0,
			_game_team_player,
			_game_team_human,
			_game_team_covenant,
			_game_team_flood,
			_game_team_sentinel,
			_game_team_unused6,
			_game_team_unused7,
			_game_team_unused8,
			_game_team_unused9,

			k_number_of_game_teams
		};
	};

	namespace GameState {
		struct s_allegiance {
			Enums::game_team this_team;
			Enums::game_team other_team;
			int16            threshold;
			UNKNOWN_TYPE(int16);   // 0x6
			UNKNOWN_TYPE(bool);      // 0x8
			UNKNOWN_TYPE(bool);      // 0x9
			bool is_broken;         // 0xA
			UNKNOWN_TYPE(bool);      // 0xB
			UNKNOWN_TYPE(bool);      // 0xC
			PAD8;
			int16 current_incidents;// 0xE
			UNKNOWN_TYPE(int16);   // 0x10
		};
		static_assert(sizeof(s_allegiance) == 0x12);

		struct s_game_allegiance_globals {
			int16        allegiances_count;
			s_allegiance allegiances[8];
			PAD16;
			long_flags ally_mapping_flags[BIT_VECTOR_SIZE_IN_DWORDS(Enums::k_number_of_game_teams * Enums::k_number_of_game_teams)]; // 0x94
			long_flags enemy_mapping_flags[BIT_VECTOR_SIZE_IN_DWORDS(Enums::k_number_of_game_teams * Enums::k_number_of_game_teams)]; // 0xA4
		}; static_assert(sizeof(s_game_allegiance_globals) == 0xB4);

		s_game_allegiance_globals *GameAllegianceGlobals();

	};

	namespace blam {
		extern cstring g_game_team_names[Enums::k_number_of_game_teams];

		// Checks to see if [team_to_test] is an enemy of [team]
		bool __cdecl game_team_is_enemy(long_enum team, long_enum team_to_test);
	};
};
