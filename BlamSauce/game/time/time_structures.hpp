#pragma once

#include <precompile.h>
#include "../configuration.h"

namespace Yelo {
	namespace GameState {
		struct s_game_time_globals {
			bool initialized;         // 0x0
			bool active;            // 0x1
			bool paused;            // 0x2
			unsigned char : 8;
			UNKNOWN_TYPE(short);      // 0x4
			UNKNOWN_TYPE(short);      // 0x6
			UNKNOWN_TYPE(short);      // 0x8
			unsigned short : 16;
			game_ticks_t game_time;      // 0xC
			game_time_t  elapsed_time;   // 0x10
			unsigned short : 16;
			game_ticks_t server_time;   // 0x14
			real         game_speed;         // 0x18
			real         leftover_time_sec;      // 0x1C
		}; static_assert(sizeof(s_game_time_globals) == 0x20);
	};
};
