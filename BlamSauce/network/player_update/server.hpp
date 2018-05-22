/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/game/game_configuration.hpp>
#include <blamlib/Halo1/game/simple_circular_queue.hpp>
#include <blamlib/Halo1/networking/player_update.hpp>

namespace Yelo
{
	namespace Networking
	{
		struct s_player_server_update
		{
			UNKNOWN_TYPE(uint32); // 0xE8
			UNKNOWN_TYPE(long);  // 0xEC
			UNKNOWN_TYPE(long);  // 0xF0
			long last_completed_update_id;
			real_point3d position;

			// 0x104 datum_index or long
			// 0x108 boolean, PAD24
			// 0x10C uint32
			// 0x110 uint32
			// 0x114 uint32
			// 0x118 uint32
			// 0x11C uint32
			// 0x120 game_ticks_t
			// 0x124 game_ticks_t
			// 0x128 long
			// 0x12C long action_baseline_id, NUMBER_OF_REMOTE_PLAYER_ACTION_UPDATE_BASELINE_IDS = 2
			// 0x130, s_remote_player_action_update_network_data
			// 0x160 uint32

			// 0x164 game_ticks_t
			// 0x168 game_ticks_t
			// 0x16C long update_id
			// 0x170 real_point3d predict_position

			// 0x17C datum_index or long
			// 0x180 datum_index or long
			// 0x184 datum_index or long
			// 0x188, 0x40 byte structure
		}; //static_assert( sizeof(s_player_server_update) == 0xE0 );

		struct update_server_queues_datum : TStructImpl(100)
		{
			//s_action_update current_action

			TStructGetPtrImpl(Memory::s_simple_circular_queue, ActionQueue, 0x28);
		};
		typedef Memory::DataArray<update_server_queues_datum, Enums::k_multiplayer_maximum_players>
			update_server_queues_data_t;

		struct s_update_server_globals
		{
			bool initialized;
			unsigned char : 8; unsigned short : 16;
			uint32 current_update_id;
			update_server_queues_data_t* queue_data;
			byte queue_data_buffer[0x308][32];
		}; static_assert( sizeof(s_update_server_globals) == 0x610C );
		s_update_server_globals* UpdateServerGlobals();
	};
};
