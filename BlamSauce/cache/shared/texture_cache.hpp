#pragma once
#include <precompile.h>

namespace Yelo::blam
	{
		void __cdecl texture_cache_open();
		void __cdecl texture_cache_close();

		// Setting [block_thread] to true causes the engine to immediately create the rasterizer (D3D) data for it
		IDirect3DBaseTexture9** __cdecl texture_cache_bitmap_get_hardware_format(TagGroups::s_bitmap_data* bitmap,
			// block
			bool block_thread = false, bool load = true);
	};
