/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/units/unit_definitions.hpp>
#include "../../../tags/group/markup.h"
#include "../object_definitions.hpp"

namespace Yelo
{
	namespace Enums
	{
		enum {
			k_max_vehicle_suspensions = 8,
		};

		enum vehicle_function_mode : short
		{
			_vehicle_function_mode_none,
			_vehicle_function_mode_speed_absolute,
			_vehicle_function_mode_speed_forward,
			_vehicle_function_mode_speed_backward,
			_vehicle_function_mode_slide_absolute,
			_vehicle_function_mode_slide_left,
			_vehicle_function_mode_slide_right,
			_vehicle_function_mode_speed_slide_maximum,
			_vehicle_function_mode_turn_absolute,
			_vehicle_function_mode_turn_left,
			_vehicle_function_mode_turn_right,
			_vehicle_function_mode_crouch,
			_vehicle_function_mode_jump,
			_vehicle_function_mode_walk,
			_vehicle_function_mode_velocity_air,
			_vehicle_function_mode_velocity_water,
			_vehicle_function_mode_velocity_ground,
			_vehicle_function_mode_velocity_forward,
			_vehicle_function_mode_velocity_left,
			_vehicle_function_mode_velocity_up,
			_vehicle_function_mode_left_tread_position,
			_vehicle_function_mode_right_tread_position,
			_vehicle_function_mode_left_tread_velocity,
			_vehicle_function_mode_right_tread_velocity,
			_vehicle_function_mode_front_left_tire_position,
			_vehicle_function_mode_front_right_tire_position,
			_vehicle_function_mode_back_left_tire_position,
			_vehicle_function_mode_back_right_tire_position,
			_vehicle_function_mode_front_left_tire_velocity,
			_vehicle_function_mode_front_right_tire_velocity,
			_vehicle_function_mode_back_left_tire_velocity,
			_vehicle_function_mode_back_right_tire_velocity,
			_vehicle_function_mode_wingtip_contrail,
			_vehicle_function_mode_hover,
			_vehicle_function_mode_thrust,
			_vehicle_function_mode_engine_hack,
			_vehicle_function_mode_wingtip_contrail_new,

			_vehicle_function_mode,
		};
		enum vehicle_type : short
		{
			_vehicle_type_human_tank,
			_vehicle_type_human_jeep,
			_vehicle_type_human_boat,
			_vehicle_type_human_plane,
			_vehicle_type_alien_scout,
			_vehicle_type_alien_fighter,
			_vehicle_type_turret,

			_vehicle_type,
		};
	};

	namespace TagGroups
	{
		struct _vehicle_definition
		{	
			struct __flags
			{
				Yelo::long_flags speed_wakes_physics_bit:1;
				Yelo::long_flags turn_wakes_physics_bit:1;
				Yelo::long_flags driver_power_wakes_physics_bit:1;
				Yelo::long_flags gunner_power_wakes_physics_bit:1;
				Yelo::long_flags control_opposite_speed_sets_brake_bit:1;
				Yelo::long_flags slide_wakes_physics_bit:1;
				Yelo::long_flags kills_riders_at_terminal_velocity_bit:1;
				Yelo::long_flags causes_collision_damage_bit:1;
				Yelo::long_flags ai_weapon_cannot_rotate_bit:1;
				Yelo::long_flags ai_does_not_require_driver_bit:1;
				Yelo::long_flags ai_unused_bit:1;
				Yelo::long_flags ai_driver_enable_bit:1;
				Yelo::long_flags ai_driver_flying_bit:1;
				Yelo::long_flags ai_driver_can_sidestep_bit:1;
				Yelo::long_flags ai_driver_hovering_bit:1;
			}; static_assert( sizeof(__flags) == sizeof(unsigned long) );

			////////////////////////////////////////////////////////////////
			// $$$ VEHICLE $$$
			__flags flags;
			short type;
			unsigned short : 16;
			real maximum_forward_speed;
			real maximum_reverse_speed;
			real speed_acceleration;
			real speed_deceleration;
			real maximum_left_turn;
			real maximum_right_turn;
			real wheel_circumference;
			real turn_rate;
			real blur_speed;
			short function_exports[Enums::k_number_of_incoming_object_functions]; // Enums::vehicle_function_mode
			long:8 * sizeof(long) * 3;
			real maximum_left_slide;
			real maximum_right_slide;
			real slide_acceleration;
			real slide_deceleration;
			real minimum_flipping_angular_velocity;
			real maximum_flipping_angular_velocity;
			long:8 * sizeof(long) * 6;
			real fixed_gun_yaw;
			real fixed_gun_pitch;
			long:8 * sizeof(long) * 6;
			real ai_sideslip_distance;
			real ai_destination_radius;
			real ai_avoidance_distance;
			real ai_pathfinding_radius;
			real ai_charge_repeat_timeout;
			real ai_strafing_abort_range;
			angle_bounds ai_oversteering_bounds;
			angle ai_steering_maximum;
			real ai_throttle_maximum;
			real ai_move_position_time;
			unsigned long : 32;
			tag_reference suspension_sound;
			tag_reference crash_sound;
			tag_reference material_effects;
			tag_reference effect;
		};

		struct s_vehicle_definition : s_unit_definition
		{
			enum { k_group_tag = 'vehi' };

			_vehicle_definition vehicle;
		}; static_assert( sizeof(s_vehicle_definition) == 0x3F0 );
	};
};
