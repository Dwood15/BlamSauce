/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include "physical_memory_map_structures.hpp"

namespace Yelo {
	namespace GameState {
		constexpr s_physical_memory_map_globals *PhysicalMemoryMapGlobals();
	};

	namespace blam {
		static void physical_memory_map_initialize();

		static void physical_memory_map_dispose();

		static inline void *physical_memory_map_get_game_state_address() {
			return GameState::PhysicalMemoryMapGlobals()->game_state_base_address;
		}

		static inline void *physical_memory_map_get_tag_cache_address() {
			return GameState::PhysicalMemoryMapGlobals()->tag_cache_base_address;
		}

		static inline void *physical_memory_map_get_sound_cache_address() {
			return GameState::PhysicalMemoryMapGlobals()->sound_cache_base_address;
		}

		static inline void *physical_memory_map_get_texture_cache_address() {
			return GameState::PhysicalMemoryMapGlobals()->texture_cache_base_address;
		}
	};
};
