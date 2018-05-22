/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

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
		sbyte   machine_index;      // 0x1C
		sbyte   controller_index;      // 0x1D
		// These values will be the same on the client as they are on the server, so
		// we can use them safely for player operations in multiplayer code
		sbyte   team_index;         // 0x1E
		sbyte   player_list_index;   // 0x1F
	}; static_assert(sizeof(s_network_game_player) == 0x20);
};
