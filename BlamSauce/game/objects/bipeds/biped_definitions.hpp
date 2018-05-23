#pragma once

#include <precompile.h>
#include "../object_definitions.hpp"
#include "../units/unit_definitions.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum biped_function_mode : short
		{
			_biped_function_mode_none,
			_biped_function_mode_flying_velocity,

			_biped_function_mode,
		};
	};

	namespace TagGroups
	{
		struct s_contact_point
		{
			long:8 * sizeof(long) * 8;
			tag_string marker_name;
		}; static_assert( sizeof(s_contact_point) == 0x40 ); // max count: 2
		struct _biped_definition
		{
			struct __flags
			{
				Yelo::long_flags turns_without_animating_bit:1;
				Yelo::long_flags uses_player_physics_bit:1;				// Halo2: removed
				Yelo::long_flags flying_bit:1;							// Halo2: removed
				Yelo::long_flags physics_pill_centered_at_origin_bit:1;	// Halo2: removed
				Yelo::long_flags spherical_bit:1;						// Halo2: removed
				Yelo::long_flags passes_through_other_bipeds_bit:1;
				Yelo::long_flags can_climb_any_surface_bit:1;			// Halo2: removed
				Yelo::long_flags immune_to_falling_damage_bit:1;
				Yelo::long_flags rotate_while_airborne_bit:1;
				Yelo::long_flags uses_limp_body_physics_bit:1;
				Yelo::long_flags has_no_dying_airborne_bit:1;			// Halo2: unused
				Yelo::long_flags random_speed_increase_bit:1;
				Yelo::long_flags unit_uses_old_ntsc_player_physics_bit:1;// Halo2: unused or removed
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			////////////////////////////////////////////////////////////////
			// $$$ BIPED $$$
			angle moving_turning_speed;
			__flags flags;
			angle stationary_turning_threshold;
			long:8 * sizeof(long) * 4;
			short function_exports[Enums::k_number_of_incoming_object_functions]; // Enums::biped_function_mode
			tag_reference dont_use;

			////////////////////////////////////////////////////////////////
			// flying
			angle bank_angle;
			real bank_apply_time;
			real bank_decay_time;
			real pitch_ratio;
			real max_velocity;
			real max_sidestep_velocity;
			real acceleration;
			real deceleration;
			angle angular_velocity_maximum;
			angle angular_acceleration_maximum;
			real crouch_velocity_modifier;
			long:8 * sizeof(long) * 2;

			////////////////////////////////////////////////////////////////
			// movement
			angle maximum_slope_angle;
			angle downhill_falloff_angle;
			angle downhill_cutoff_angle;
			real downhill_velocity_scale;
			angle uphill_falloff_angle;
			angle uphill_cutoff_angle;
			real uphill_velocity_scale;
			long:8 * sizeof(long) * 6;
			tag_reference footsteps;
			long:8 * sizeof(long) * 6;

			////////////////////////////////////////////////////////////////
			// jumping and landing
			real jump_velocity;
			long:8 * sizeof(long) * 7;
			real maximum_soft_landing_time;
			real maximum_hard_landing_time;
			real minimum_soft_landing_velocity;
			real minimum_hard_landing_velocity;
			real maximum_hard_landing_velocity;
			real death_hard_landing_velocity;
			long:8 * sizeof(long) * 5;

			////////////////////////////////////////////////////////////////
			// camera, collision, and autoaim
			real standing_camera_height;
			real crouching_camera_height;
			real crouch_transition_time;
			long:8 * sizeof(long) * 6;
			real standing_collision_height;
			real crouching_collision_height;
			real collision_radius;
			long:8 * sizeof(long) * 10;
			real autoaim_width;
			long:8 * sizeof(long) * 35;
			TAG_TBLOCK(contact_points, s_contact_point);
		};

		struct s_biped_definition : s_unit_definition
		{
			enum { k_group_tag = 'bipd' };

			_biped_definition biped;
		}; static_assert( sizeof(s_biped_definition) == 0x4F4 );
	};
};
