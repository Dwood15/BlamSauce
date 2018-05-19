#include <precompile.h>
#pragma once
/*
k_maximum_player_skill_level	127
k_maximum_player_experience		0x3FFFFFFF

k_maximum_teams					16
*/

namespace Yelo::Enums {
	enum {
		k_maximum_round_index = 31,

		k_multiplayer_team_count = 8,

		k_maximum_candy_monitors = 100,
	};
};

namespace Yelo::Game {
	struct s_game_results_player_statistics {};
	struct s_game_results_team_statistics {};
	struct s_game_results_statistics {};
	struct s_game_results {
		bool finalized;
			  PAD24;
	};

	struct s_game_result_globals {
		bool recording;
		bool pause;
		bool updating;
			  PAD8;
	};
};
