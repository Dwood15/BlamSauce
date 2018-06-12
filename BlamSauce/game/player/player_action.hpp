#pragma once
#include <precompile.h>
#include "../../cseries/base.h"

namespace Yelo
{
	namespace Enums
	{
		enum player_action_result
		{
			_player_action_result_none,
			_player_action_result_pickup_powerup,
			_player_action_result_swap_powerup,
			_player_action_result_exit_seat,
			_player_action_result_4, // game engine related

			_player_action_result_swap_equipment,
			_player_action_result_swap_weapon,
			_player_action_result_pickup_weapon,

			_player_action_result_enter_seat,
			_player_action_result_force_ai_to_exit_seat,
			_player_action_result_touch_device,
			_player_action_result_flip_vehicle,

			k_number_of_player_action_results,

			k_number_of_player_action_results_yelo = k_number_of_player_action_results,
		};
	};

	namespace Players
	{
		struct s_player_action_result
		{
			datum_index action_object_index;
			short action_result;			// enum object_type
			short action_seat_index;
		}; static_assert( sizeof(s_player_action_result) == 0x8 );

		struct s_player_action
		{
			unsigned long control_flags;
			real_euler_angles2d desired_facing;
			real_vector2d throttle;
			float primary_trigger;
			short desired_weapon_index, desired_grenade_index;
			short desired_zoom_index;
			unsigned short : 16;
		}; static_assert( sizeof(s_player_action) == 0x20 );

		struct s_player_set_action_result_network_data
		{
			datum_index player_index;
			unsigned long action_result_type;
			s_player_action_result action;
			datum_index weapon_to_drop_as_result_of_swap;
		}; static_assert( sizeof(s_player_set_action_result_network_data) == 0x14 );
	};
};
