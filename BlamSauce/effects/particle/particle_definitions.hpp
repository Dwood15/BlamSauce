/*
	Yelo: Open Sauce SDK
		Halo 1 (Editing Kit) Edition

	See license\OpenSauce\Halo1_CheApe for specific license information
*/
#pragma once

#include <blamlib/Halo1/shaders/shader_definitions.hpp>
#include "../../tags/group/markup.h"
#include "../shader/shader_definitions.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum particle_orientation : short
		{
			_particle_orientation_screen_facing,
			_particle_orientation_parallel_to_direction,
			_particle_orientation_perpendicular_to_direction,

			_particle_orientation,
		};
	};
	namespace TagGroups
	{
		struct s_particle_definition
		{
			enum { k_group_tag = 'part' };

			struct __flags
			{
				Yelo::long_flags can_animate_backwards_bit:1;
				Yelo::long_flags animation_stops_at_rest_bit:1;
				Yelo::long_flags animation_starts_on_random_frame_bit:1;
				Yelo::long_flags animate_once_per_frame_bit:1;
				Yelo::long_flags dies_at_rest_bit:1;
				Yelo::long_flags dies_on_contact_with_structure_bit:1;
				Yelo::long_flags tint_from_diffuse_texture_bit:1;
				Yelo::long_flags dies_on_contact_with_water_bit:1;
				Yelo::long_flags dies_on_contact_with_air_bit:1;
				Yelo::long_flags self_illuminated_bit:1;
				Yelo::long_flags random_horizontal_mirroring_bit:1;
				Yelo::long_flags random_vertical_mirroring_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			__flags flags;
			tag_reference bitmap;
			tag_reference physics;
			tag_reference marty_traded_his_kids_for_this;
			unsigned long : 32;
			real_bounds lifespan;
			real fade_in_time;
			real fade_out_time;
			tag_reference collision_effect;
			tag_reference death_effect;
			real minimum_size;
			long:8 * sizeof(long) * 2;
			real_bounds radius_animation;
			unsigned long : 32;
			real_bounds animation_rate;
			real contact_deterioration;
			real fade_start_size;
			real fade_end_size;
			unsigned long : 32;
			short first_sequence_index;
			short initial_sequence_count;
			short looping_sequence_count;
			short final_sequence_count;

			long:8 * sizeof(long) * 3;
			short orientation;
			unsigned short : 16;
			s_shader_effect shader_effect;
		}; static_assert( sizeof(s_particle_definition) == 0x164 ); // max count: 1
	};
};
