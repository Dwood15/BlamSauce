#pragma once

#include <precompile.h>>
#include "../memory/upgrades/blam_memory_upgrades.hpp"
#include "shared/pc_texture_cache.hpp"
#include "shared/pc_sound_cache.hpp"
#include "../memory/lruv_cache.h"

namespace Yelo::GameState
	{
		// Made up structure for Halo1
		template<typename DatumT, size_t MaxDatumCount, size_t MaxDatumCountUpgrade = MaxDatumCount>
		struct s_resource_cache
		{
			Memory::DataArray<DatumT, MaxDatumCount, MaxDatumCountUpgrade>* data;
			void* base_address;
			Memory::s_lruv_cache* lruv_cache;
			bool initialized;
			unsigned char : 8; unsigned short : 16;
		};

		struct s_physical_memory_map_globals
		{
			s_resource_cache<	Cache::s_sound_cache_datum, Yelo::Enums::k_maximum_number_of_cached_sounds> pc_sound_cache;
			s_resource_cache<Cache::s_texture_cache_datum, Yelo::Enums::k_maximum_number_of_cached_textures> pc_texture_cache;

			void* game_state_base_address;
			void* tag_cache_base_address;
			void* texture_cache_base_address;
			void* sound_cache_base_address;
		};
	};
