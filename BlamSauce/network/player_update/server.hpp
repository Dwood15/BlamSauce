#pragma once

#include <precompile.h>

namespace Yelo
{
	namespace Networking
	{
		struct s_player_server_update
		{
			UNKNOWN_TYPE(uint); // 0xE8
			UNKNOWN_TYPE(long);  // 0xEC
			UNKNOWN_TYPE(long);  // 0xF0
			long last_completed_update_id;
			real_point3d position;

			// 0x104 datum_index or long
			// 0x108 boolean, PAD24
			// 0x10C uint
			// 0x110 uint
			// 0x114 uint
			// 0x118 uint
			// 0x11C uint
			// 0x120 game_ticks_t
			// 0x124 game_ticks_t
			// 0x128 long
			// 0x12C long action_baseline_id, NUMBER_OF_REMOTE_PLAYER_ACTION_UPDATE_BASELINE_IDS = 2
			// 0x130, s_remote_player_action_update_network_data
			// 0x160 uint

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
		typedef Memory::DataArray<update_server_queues_datum, Enums::k_multiplayer_maximum_players> update_server_queues_data_t;

		struct s_update_server_globals
		{
			bool initialized;
			unsigned char : 8; unsigned short : 16;
			uint current_update_id;
			update_server_queues_data_t* queue_data;
			byte queue_data_buffer[0x308][32];
		}; static_assert( sizeof(s_update_server_globals) == 0x610C );
		s_update_server_globals* UpdateServerGlobals();
	};
};
