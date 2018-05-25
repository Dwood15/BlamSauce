#pragma once

#include <precompile.h>
#include "../../memory/data_base.h"
#include "../../tags/bitmap_grp.h"
#include "../../hs/runtime.hpp"
#include "../../scenario/scenario.h"
#include "../../hs/hs.h"
#include "../../hs/structures.hpp"

namespace Yelo {
	namespace Cache {
		struct s_texture_cache_datum : Memory::s_datum_base {
			short cache_read_request_index;
			bool  finished_loading_flag;
			bool  valid; // set to true when finished loading and the texture request populates hardware_format
			unsigned short : 16;
			TagGroups::s_bitmap_data *bitmap;
			IDirect3DBaseTexture9    *hardware_format; // the address of this field is returned by the texture request function
		}; static_assert(sizeof(s_texture_cache_datum) == 0x10);
	};

	namespace blam {
		using namespace TagGroups;

		void __cdecl texture_cache_open() { assert(false); } //, "this isn't implemented yet");

		void __cdecl texture_cache_close() { assert(false); } //, "this isn't implemented yet");

		IDirect3DBaseTexture9 **__cdecl texture_cache_bitmap_get_hardware_format_impl(TagGroups::s_bitmap_data *bitmap, bool block_thread, bool load) {
			assert(bitmap && bitmap->signature == s_bitmap_group::k_group_tag);

			// assert(false);//, "this isn't implemented yet");

			return CAST_PTR(IDirect3DBaseTexture9**, bitmap->hardware_format);
		}
	};
};
