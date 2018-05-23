#pragma once

#include <precompile.h>
#include "../../memory/data_base.h"

namespace Yelo {

	namespace Cache {
		struct s_sound_cache_datum : Memory::s_datum_base {
			bool finished_loading_flag;               // 0x2
			UNKNOWN_TYPE(bool);                     // 0x3 true when the sound contains decompressed xbox adpcm samples
			UNKNOWN_TYPE(byte);                     // 0x4 haven't seen this used, don't know the exact type
			sbyte software_reference_count;            // 0x5
			sbyte hardware_reference_count;            // 0x6
			UNKNOWN_TYPE(byte);                     // 0x7 haven't seen this used, don't know the exact type
			short cache_read_request_index;
			unsigned short : 16;
			TagGroups::s_sound_permutation *sound;
		}; static_assert(sizeof(s_sound_cache_datum) == 0x10);
	};

	namespace blam {
		static inline void __cdecl sound_cache_open() {
			assert(false); //, "not implemented yet!"); }

			static inline void __cdecl sound_cache_close() {
				assert(false); //, "not implemented yet!"); }

				static inline bool __cdecl sound_cache_sound_request_impl(TagGroups::s_sound_permutation *sound, bool block_thread, bool load, bool reference) {
					bool success = false;

					assert(load || !block_thread);
					assert(load || !reference);
					assert(sound->cache_tag_index.handle != 0); // yes, the engine checks against 0, which is why we have to use .handle

					if (sound->cache_block_index.IsNull() && load) {
						assert(false, "this isn't implemented yet");
					}

					if (sound->cache_block_index.IsNull())
						return false;

					assert(false, "this isn't implemented yet");

					return success;
				}

				static inline void __cdecl sound_cache_sound_finished(TagGroups::s_sound_permutation *sound) { assert(false, "this isn't implemented yet"); }
			};
		};
