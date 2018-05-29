#pragma once

#include <precompile.h>
#include "../player/players.hpp"

namespace Yelo::GameEngine {
		struct s_ctf_globals
		{
			real_point3d* team_flag_positions[Enums::k_number_of_multiplayer_teams];
			datum_index team_flag_object_indexes[Enums::k_number_of_multiplayer_teams]; // weapon objects
			long team_score[Enums::k_number_of_multiplayer_teams];
			long score_limit;
			bool team_flag_is_taken[Enums::k_number_of_multiplayer_teams];
			unsigned short : 16;
			uint team_flag_is_taken_sound_timer[Enums::k_number_of_multiplayer_teams];
			uint flag_swap_timer;
			uint flag_failure_sound_timer;
			byte team_with_flag;
			unsigned char : 8; unsigned short : 16;
		}; static_assert( sizeof(s_ctf_globals) == 0x34 );
	};
