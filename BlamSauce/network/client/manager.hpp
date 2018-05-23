#pragma once

#include "manager_structures.hpp"

namespace Yelo::Enums {
	enum network_game_client_state : short {
		_network_game_client_state_searching,
		_network_game_client_state_joining,
		_network_game_client_state_pregame,
		_network_game_client_state_ingame,
		_network_game_client_state_postgame,

		_network_game_client_state,
	};
};

namespace Yelo::Networking {

	// Gets the network game client pointer
	s_network_game_client *NetworkGameClient();
};
};
