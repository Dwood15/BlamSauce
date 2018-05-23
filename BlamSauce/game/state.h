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
			uint allocation_crc;
			char level[256];
			tag_string version;
			short player_spawn_count;
			short game_difficulty;
			uint cache_crc;

			union {
				byte _unused[32];
				s_yelo_header_data yelo;
			};
		}; static_assert( sizeof(s_header_data) == 0x14C );

		struct s_game_state_globals
		{
			void* base_address;
			uint cpu_allocation_size;
			uint gpu_allocation_size; // unused
			uint crc;
			bool locked;
			bool saved;
					 unsigned short : 16;
			uint revert_time;
			s_header_data* header;
			HANDLE autosave_thread;
			bool buffer_allocated;
			unsigned char : 8; unsigned short : 16;
			void* buffer;
			uint buffer_size;
			bool file_open;
			bool file_valid_for_read;
					 unsigned short : 16;
			HANDLE file_handle;
			char file_path[256];
			char core_path[256];
			HANDLE autosave_event;
			bool autosave_finished;
			bool creating_autosave;
					 unsigned short : 16;
		}; static_assert( sizeof(s_game_state_globals) == 0x23C );
	};
};
