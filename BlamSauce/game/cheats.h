/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo
{
	namespace blam
	{
		// Spawn all weapons referenced in the game globals around the player_update
		void __cdecl cheat_all_weapons();

		// Spawn a warthog near the player_update
		void __cdecl cheat_spawn_warthog();

		// Teleport the player_update to the camera's active position
		void __cdecl cheat_teleport_to_camera();

		// Activates camo on [cheat_local_player()]
		void __cdecl cheat_active_camouflage();

		// Activates camo on the local player_update
		void __cdecl cheat_active_camouflage_local_player();

		// Gets the player_update for cheating in this game
		datum_index __cdecl cheat_local_player();
	};
};
