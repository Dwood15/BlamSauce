/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/game/game_configuration.hpp>
#include <blamlib/Halo1/game/players.hpp>

namespace Yelo
{
	namespace GameEngine
	{
		struct s_oddball_globals
		{
			long score_to_win;
			long team_score[Enums::k_multiplayer_maximum_players];
			long individual_score[Enums::k_multiplayer_maximum_players];
			long undocumented1[Enums::k_multiplayer_maximum_players];
			datum_index current_ball_owners[Enums::k_multiplayer_maximum_players]; // player_index
			long current_ball_held_times[Enums::k_multiplayer_maximum_players]; // game-ticks
		}; //static_assert( sizeof(s_slayer_globals) == 0x );
	};
};
