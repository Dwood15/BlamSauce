#pragma once

#include <precompile.h>
#include "../../tags/group/markup.h"
#include "../../tags/group/tag_groups_base_yelo.hpp"
#include "../shader/shader_definitions.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum particle_creation_physics : short
		{
			_particle_creation_physics_default,
			_particle_creation_physics_explosion,
			_particle_creation_physics_jet,

			_particle_creation_physics,
		};
		enum particle_update_physics : short
		{
			_particle_update_physics_default,

			_particle_update_physics,
		};
		enum complex_sprite_render_modes : short
		{
			_complex_sprite_render_modes_simple,
			_complex_sprite_render_modes_rotational,

			_complex_sprite_render_modes,
		};
		enum system_update_physics : short
		{
			_system_update_physics_default,
			_system_update_physics_explosion,

			_system_update_physics,
		};
	};
	namespace TagGroups
	{
		struct s_particle_system_physics_constants
		{
			real k;
		}; static_assert( sizeof(s_particle_system_physics_constants) == 0x4 ); // max count: 16

		struct s_particle_system_type_states
		{
			tag_string name;
			real_bounds duration_bounds;
			real_bounds transition_time_bounds;
			unsigned long : 32;
			real scale_multiplier;
			real animation_rate_multiplier;
			real rotation_rate_multiplier;
			real_argb_color color_multiplier;
			real radius_multiplier;
			real minimum_particle_count;
			real particle_creation_rate;
			long:8 * sizeof(long) * 21;
			Enums::particle_creation_physics particle_creation_physics;
			Enums::particle_update_physics particle_update_physics;
			Yelo::TagBlock<const s_particle_system_physics_constants> physics_constants;
		}; static_assert( sizeof(s_particle_system_type_states) == 0xC0 ); // max count: 8

		struct s_particle_system_type_particle_states
		{
			tag_string name;
			real_bounds duration_bounds;
			real_bounds transition_time_bounds;
			tag_reference bitmaps;
			short sequence_index;
			unsigned short : 16;
			unsigned long : 32;
			real_bounds scale;
			real_bounds animation_rate;
			angle_bounds rotation_rate;
			real_argb_color color_1;
			real_argb_color color_2;
			real radius_multiplier;
			tag_reference point_physics;
			long:8 * sizeof(long) * 9;
			s_shader_effect shader_effect;
			Yelo::TagBlock<const s_particle_system_physics_constants> physics_constants;
		}; static_assert( sizeof(s_particle_system_type_particle_states) == 0x178 ); // max count: 8

		struct s_particle_system_types
		{
			struct __flags
			{
				Yelo::long_flags type_states_loop_bit:1;
				Yelo::long_flags _forward_backward_bit:1;
				Yelo::long_flags particle_states_loop_bit:1;
				Yelo::long_flags _forward_backward_1_bit:1;
				Yelo::long_flags particles_die_in_water_bit:1;
				Yelo::long_flags particles_die_in_air_bit:1;
				Yelo::long_flags particles_die_on_ground_bit:1;
				Yelo::long_flags rotational_sprites_animate_sideways_bit:1;
				Yelo::long_flags disabled_bit:1;
				Yelo::long_flags tint_by_effect_color_bit:1;
				Yelo::long_flags initial_count_scales_with_effect_bit:1;
				Yelo::long_flags minimum_count_scales_with_effect_bit:1;
				Yelo::long_flags creation_rate_scales_with_effect_bit:1;
				Yelo::long_flags scale_scales_with_effect_bit:1;
				Yelo::long_flags animation_rate_scales_with_effect_bit:1;
				Yelo::long_flags rotation_rate_scales_with_effect_bit:1;
				Yelo::long_flags don_t_draw_in_first_person_bit:1;
				Yelo::long_flags don_t_draw_in_third_person_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			struct __physics_flags
			{
				Yelo::long_flags unused_bit:1;
			}; static_assert( sizeof(__physics_flags) == sizeof(unsigned long) );

			tag_string name;
			__flags flags;
			short initial_particle_count;
			unsigned short : 16;
			Enums::complex_sprite_render_modes complex_sprite_render_modes;
			unsigned short : 16;
			real radius;
			long:8 * sizeof(long) * 9;
			Enums::particle_creation_physics particle_creation_physics;
			unsigned short : 16;
			__physics_flags physics_flags;
			Yelo::TagBlock<const s_particle_system_physics_constants> physics_constants;
			Yelo::TagBlock<const s_particle_system_type_states> states;
			Yelo::TagBlock<const s_particle_system_type_particle_states> particle_states;
		}; static_assert( sizeof(s_particle_system_types) == 0x80 ); // max count: 4

		struct s_particle_system_definition
		{
			enum { k_group_tag = 'pctl' };

			struct __physics_flags
			{
				Yelo::long_flags unused_bit:1;
			}; static_assert( sizeof(__physics_flags) == sizeof(unsigned long) );

			unsigned long : 32;
			long:8 * sizeof(long) * 13;

			////////////////////////////////////////////////////////////////
			// system behavior
			// These settings affect the behavior of the system's origin.
			tag_reference point_physics;
			Enums::system_update_physics system_update_physics;
			unsigned short : 16;
			__physics_flags physics_flags;
			Yelo::TagBlock<const s_particle_system_physics_constants> physics_constants;
			Yelo::TagBlock<const s_particle_system_types> particle_types;
		}; static_assert( sizeof(s_particle_system_definition) == 0x68 ); // max count: 1
	};
};
