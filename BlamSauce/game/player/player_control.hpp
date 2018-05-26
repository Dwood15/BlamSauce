#pragma once

#include <precompile.h>
#include "../../math/real_math.h"
#include "../objects/units/unit_camera.hpp"

namespace Yelo
{
	namespace Players
	{
		struct s_player_control
		{
			datum_index unit_index;									// 0x0
			unsigned long control_flags;								// 0x4
			unsigned short : 16; // unknown field									// 0x8
			unsigned short : 16; // unknown field									// 0xA
			real_euler_angles2d	 desired_angles;					// 0xC
			real_vector2d throttle;									// 0x14
			real primary_trigger;									// 0x1C
			short weapon_index;										// 0x20
			short grenade_index;									// 0x22
			short zoom_level;										// 0x24
			sbyte weapon_swap_ticks; // unknown field				// 0x26
			unsigned char : 8; // unknown field									// 0x27
			datum_index target_object_index;						// 0x28
			real autoaim_level;										// 0x2C
			unsigned long : 32; // unknown field									// 0x30
			unsigned long : 32;													// 0x34
			unsigned long : 32; // unknown field									// 0x38
			unsigned long : 32; // unknown field									// 0x3C
		}; static_assert( sizeof(s_player_control) == 0x40 );

		struct s_player_control_globals_data
		{
			unsigned long action_flags[2]; // see "action_test" script functions
			unsigned long : 32; // TODO: document the fields in the first 12 bytes of this struct
			unsigned long flags; // FLAG(0) = camera control

			s_player_control local_players[Enums::k_maximum_number_of_local_players];
		}; static_assert( sizeof(s_player_control_globals_data) == 0x50 );

		struct s_unit_camera_info
		{
			datum_index unit_index;
			short seat_index;
			unsigned short : 16;
			const TagGroups::s_unit_camera* unit_camera_definition;
			real_point3d position;
		}; static_assert( sizeof(s_unit_camera_info) == 0x18 );

		s_player_control_globals_data*	PlayerControlGlobals();
	};

	namespace blam
	{
		void __cdecl player_control_get_unit_camera_info(const short player_index, Players::s_unit_camera_info& camera_info);
	};
};
