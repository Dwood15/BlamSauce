/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <winnt.h>
#include "../cseries/base.h"
#include "../hs/types_runtime.inl"
#include "../memory/upgrades/game_state_yelo.hpp"

namespace Yelo
{
	namespace GameState
	{
		namespace Enums
		{
			enum {
				k_game_state_allocation_size = 0x00440000,

				// Max amount of memory addressable by the game state. After this comes tag memory
					k_game_state_cpu_size = k_game_state_allocation_size,
			};
		};

		namespace GameState
		{
			struct s_header_data;
			struct s_game_state_globals;

			s_game_state_globals* GameStateGlobals();
		};

		namespace blam
		{
			void* __cdecl game_state_malloc(cstring name, cstring type, size_t size);
		};

		struct s_header_data
		{
			uint32 allocation_crc;
			char level[256];
			tag_string version;
			int16 player_spawn_count;
			short game_difficulty;
			uint32 cache_crc;

			union {
				byte _unused[32];
				s_yelo_header_data yelo;
			};
		}; static_assert( sizeof(s_header_data) == 0x14C );

		struct s_game_state_globals
		{
			void* base_address;
			uint32 cpu_allocation_size;
			uint32 gpu_allocation_size; // unused
			uint32 crc;
			bool locked;
			bool saved;
					 PAD16;
			uint32 revert_time;
			s_header_data* header;
			HANDLE autosave_thread;
			bool buffer_allocated; PAD24;
			void* buffer;
			uint32 buffer_size;
			bool file_open;
			bool file_valid_for_read;
					 PAD16;
			HANDLE file_handle;
			char file_path[256];
			char core_path[256];
			HANDLE autosave_event;
			bool autosave_finished;
			bool creating_autosave;
					 PAD16;
		}; static_assert( sizeof(s_game_state_globals) == 0x23C );
	};
};