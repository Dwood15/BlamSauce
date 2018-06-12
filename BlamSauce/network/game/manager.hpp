#pragma once
#include <precompile.h>
#include "../../game/player/player_control.hpp"

namespace Yelo::Enums {
	enum {
		k_network_game_maximum_player_count = k_multiplayer_maximum_players,
	};
};

namespace Yelo::Networking {
	struct s_network_game_player {
		wchar_t name[Enums::k_player_name_length + 1];   // 0x0
		short   primary_color_index;   // 0x18
		short   icon_index;         // 0x1A
		signed char   machine_index;      // 0x1C
		signed char   controller_index;      // 0x1D
		// These values will be the same on the client as they are on the server, so
		// we can use them safely for player operations in multiplayer code
		signed char   team_index;         // 0x1E
		signed char   player_list_index;   // 0x1F
	}; static_assert(sizeof(s_network_game_player) == 0x20);
};
