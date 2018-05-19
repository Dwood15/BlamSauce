/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <precompile.h>
#include "../memory/simple_circular_queue.h"

namespace Yelo::Game {
	struct s_action_queue_entry : TStructImpl(44) {
		// 0x4 int32 remaining_ticks_to_apply_action_to
	};
	struct s_action_queue {
		Memory::s_simple_circular_queue queue;
		s_action_queue_entry            *entries;         // 0x14, #120, user_data
		bool                            action_is_valid;               // 0x18
		PAD24;
		Yelo::Players::s_player_action action;      // 0x1C
	}; static_assert(sizeof(s_action_queue) == 0x3C);
};
