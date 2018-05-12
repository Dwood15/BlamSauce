#pragma once

#include "../cseries/cseries_base.h"
#include "../tag_helpers/tag_groups_markup.h"
#include "../math/real_math.h"
#include "../math/color_math.h"
#include "../tag_helpers/tag_groups_base.h"

namespace Yelo {
	namespace Scenario {
		struct s_scenario_player_atmospheric_fog // made up name
		{
			bool is_inside;
			PAD24;
			UNKNOWN_TYPE(real_vector3d);
			UNKNOWN_TYPE(real_vector3d);
			UNKNOWN_TYPE(real_rgb_color);
			UNKNOWN_TYPE(real);
		}; static_assert(sizeof(s_scenario_player_atmospheric_fog) == 0x2C);

		struct sound_environment {
			PAD32;
			int16 priority;
			PAD16;
			real room_intensity_db;
			real room_intensity_hf_db;
			real room_rolloff_factor;
			real decay_time;
			real decay_hf_ratio;
			real reflections_intensity_db;
			real reflections_delay;
			real reverb_intensity_db;
			real reverb_delay;
			real diffusion;
			real density;
			real hf_reference;
			PAD128;
		};
		static_assert( sizeof(sound_environment) == 0x48 );

	struct s_scenario_globals {
		int16 current_structure_bsp_index;
		PAD16;
		s_scenario_player_atmospheric_fog player_fog[/* Enums::k_maximum_number_of_local_players*/ 1];
		struct {
			bool copy_environment_tag;
			PAD24; // never seen this set to true
			sound_environment environment;
		}                                 sound;
	}; static_assert(sizeof(s_scenario_globals) == 0x7C);

	// The engine uses this for things (objects, ai, etc) which get dis/connected to the scenario's bsp
	struct s_scenario_location {
		int32 leaf_index;
		int16 cluster_index;
		UNKNOWN_TYPE(int16);
	}; static_assert(sizeof(s_scenario_location) == 0x8);

	struct s_sky_atmospheric_fog {
		real_rgb_color color;
		PAD64;
		real_fraction maximum_density;
		real          start_distance;
		real          opaque_distance;
	};
	static_assert(sizeof(s_sky_atmospheric_fog) == 0x20);

	struct s_sky_definition {
		enum { k_group_tag = 'sky ' };

		tag_reference         model;
		tag_reference         animation;
		TAG_PAD(ssky, tag_block, 2);
		struct s_ambient_radiosity {
			real_rgb_color color;
			real           power;
		}                     indoor_ambience, outdoor_ambience;
		s_sky_atmospheric_fog outdoor_fog, indoor_fog;
		tag_reference         indoor_fog_screen; // 'fog '
		PAD32; // this could be angle 'Global Sky Rotation' (a la Halo 2). TODO: try to find references to this field offset
		TAG_PAD(ssky1,
				  tag_block,
				  1 + // s_sky_shader_function
				  1 + // s_sky_animation
				  1); // s_sky_light
	};
	static_assert(sizeof(s_sky_definition) == 0xD0);

};
};
