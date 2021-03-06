/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo {
	namespace TagGroups {
		struct model_animation_graph;
	};

	namespace Enums {
		enum animation_update_kind : signed long {
			_animation_update_kind_render_only,
			_animation_update_kind_affects_game_state,
		};
	};

	namespace Animations {
		struct s_animation_list_entry {
			const char * name;
			short   type;
					  unsigned short : 16;
		}; static_assert(sizeof(s_animation_list_entry) == 0x8);
		struct s_animation_list {
			short count;
					unsigned short : 16;
			s_animation_list_entry *entries;
		}; static_assert(sizeof(s_animation_list) == 0x8);
	};

	namespace Objects {
		struct s_animation_state {
			short animation_index;
			short frame_index;
		}; static_assert(sizeof(s_animation_state) == 0x4);
	};

	namespace blam {
		// If the animation at [animation_index] in [animation_graph_index] is permutated, this will randomly pick one of them.
		// Returns the random [animation_index]
		short __cdecl animation_choose_random_permutation_internal(signed long render_or_affects_game_state, datum_index animation_graph_index, long animation_index);
	};
};
