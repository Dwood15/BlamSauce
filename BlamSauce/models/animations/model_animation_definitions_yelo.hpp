/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "definitions.hpp"
#include "../../tags/group/markup.h"
#include "../../tags/group/base.h"

namespace Yelo {
	namespace Enums {
		enum {
			k_max_effect_references_per_graph = Enums::k_max_sound_references_per_graph_upgrade,
		};
		enum equipment_animation {
			k_number_of_equipment_animations,
		};

		enum projectile_animation {
			k_number_of_projectile_animations,
		};
	};

	namespace TagGroups {
		// The actual definition part of an OS-extended
		struct model_animation_graph_yelo_definition {
			TAG_FIELD(tag_reference, stock_animation, 'antr');
			TAG_PAD(magyd_pad0, tag_block, 13);
		}; static_assert(sizeof(model_animation_graph_yelo_definition) == 0xAC);
		struct model_animation_graph_yelo {
			enum { k_group_tag = 'magy' };

			model_animation_graph                 stock_graph;
			model_animation_graph_yelo_definition yelo_graph;
		};
	};
};
