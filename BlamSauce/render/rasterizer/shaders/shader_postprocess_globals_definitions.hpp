#pragma once

#include <precompile.h>

namespace Yelo::TagGroups {
	struct s_shader_postprocess_bloom_definition {
		real          size;
		real          exposure;
		real_fraction mix_amount;

		real_rgb_color minimum_color;
		real_rgb_color maximum_color;
	};

	struct s_shader_postprocess_globals_bloom {
		struct _flags {
			unsigned short is_enabled_bit:1;
			unsigned short apply_after_hud_bit:1;
		} flags;
		unsigned short : 16;

		s_shader_postprocess_bloom_definition bloom;
	}; static_assert(sizeof(s_shader_postprocess_globals_bloom) == 0x28);

	struct s_shader_postprocess_globals {
		enum { k_group_tag = 'sppg' };

		unsigned short : 16;
		unsigned short : 16;
		union {
			tag_block:8 * sizeof(tag_block) * 20; // Up to to 20 blocks for subsystem globals

			struct {
				Yelo::TagBlock<s_shader_postprocess_globals_bloom> bloom_globals;
			};
		};
	}; static_assert(sizeof(s_shader_postprocess_globals) == 0xF4);
};

