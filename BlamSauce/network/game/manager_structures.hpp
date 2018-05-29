#pragma once

#include <precompile.h>
#include "../../game/engines/variants.h"

namespace Yelo::Networking
	{
		struct s_network_game_map
		{
			long version;
			char name[128];
		}; static_assert( sizeof(s_network_game_map) == 0x84 );

		struct s_network_game
		{
			wchar_t name[64];						// 0x0
			s_network_game_map map;					// 0x80
			GameEngine::s_game_variant game_variant;// 0x104
			byte _unused_game_engine;				// 0x1DC
			byte maximum_players;					// 0x1DD
			short difficulty_level;					// 0x1DE
			short player_count;						// 0x1E0
			s_network_game_player players[Enums::k_network_game_maximum_player_count];	// 0x1E2
			unsigned short : 16;									// 0x3E2
			long network_game_random_seed;			// 0x3E4
			long number_of_games_played;			// 0x3E8
			long local_data;						// 0x3EC
		}; static_assert( sizeof(s_network_game) == 0x3F0 );

		// For increased player counts game states
		struct s_network_game_yelo : s_network_game
		{
			s_network_game_player players_yelo[Enums::k_maximum_network_machine_count_upgrade];
		};
	};
};
