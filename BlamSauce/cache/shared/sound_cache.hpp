#pragma once
#include <precompile.h>

namespace Yelo::blam
	{
		void __cdecl sound_cache_open();
		void __cdecl sound_cache_close();

		bool __cdecl sound_cache_sound_request(TagGroups::s_sound_permutation* sound,
			// block										increment software_reference_count
			bool block_thread = false, bool load = true, bool reference = false);

		void __cdecl sound_cache_sound_finished(TagGroups::s_sound_permutation* sound);
	};
};
