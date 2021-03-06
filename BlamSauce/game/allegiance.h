/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <precompile.h>


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
			short            threshold;
			UNKNOWN_TYPE(short);   // 0x6
			UNKNOWN_TYPE(bool);      // 0x8
			UNKNOWN_TYPE(bool);      // 0x9
			bool is_broken;         // 0xA
			UNKNOWN_TYPE(bool);      // 0xB
			UNKNOWN_TYPE(bool);      // 0xC
			unsigned char : 8;
			short current_incidents;// 0xE
			UNKNOWN_TYPE(short);   // 0x10
		};
		static_assert(sizeof(s_allegiance) == 0x12);

		struct s_game_allegiance_globals {
			short        allegiances_count;
			s_allegiance allegiances[8];
			unsigned short : 16;
			unsigned long ally_mapping_flags[BIT_VECTOR_SIZE_IN_DWORDS(Enums::k_number_of_game_teams * Enums::k_number_of_game_teams)]; // 0x94
			unsigned long enemy_mapping_flags[BIT_VECTOR_SIZE_IN_DWORDS(Enums::k_number_of_game_teams * Enums::k_number_of_game_teams)]; // 0xA4
		}; static_assert(sizeof(s_game_allegiance_globals) == 0xB4);

		s_game_allegiance_globals *GameAllegianceGlobals();

	};

	namespace blam {
		extern const char * g_game_team_names[Enums::k_number_of_game_teams];

		// Checks to see if [team_to_test] is an enemy of [team]
		bool __cdecl game_team_is_enemy(signed long team, signed long team_to_test);
	};
};
