/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_maximum_number_of_local_players = 4,
			k_multiplayer_maximum_players = 16,

			// for team_data (which has a maximum of 16 datums) and such.
			// This is 1 in Stubbs, I'm positive team_data uses k_multiplayer_maximum_players. 
			k_multiplayer_maximum_teams = k_multiplayer_maximum_players,
		};
	};

	/// <summary>	The integral type used to represent game ticks. </summary>
	typedef long game_ticks_t;
	/// <summary>	The integral type used to represent (relative) game timers. </summary>
	/// <remarks>	Steps are in ticks. Generally used for countdowns </remarks>
	typedef short game_time_t;
};
