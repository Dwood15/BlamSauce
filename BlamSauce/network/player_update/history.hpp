/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include <blamlib/Halo1/objects/object_structures.hpp>
#include <blamlib/Halo1/units/unit_structures.hpp>
#include <blamlib/Halo1/units/biped_structures.hpp>
#include <blamlib/Halo1/units/vehicle_structures.hpp>

namespace Yelo
{
	namespace Networking
	{
		struct s_player_update
		{
			long id;
			long tick_count;
			byte action_collection[32];
			bool driving_vehicle;
			unsigned char : 8; unsigned short : 16;
			struct {
				datum_index parent_object_index;
				real_point3d position;
				real_vector3d transitional_velocity;
				real_vector3d forward;
				Objects::s_object_datum_animation_data animation;
			}object;
			struct {
				Objects::s_unit_datum_animation_data animation;
				//////////////////////////////////////////////////////////////////////////
				// seat related
				real_vector3d unit_34C;
				real_vector3d unit_358;
				real_vector3d unit_364;
				real_vector3d unit_370;
			}unit;

			struct {
				long_flags flags;
				sbyte biped_503;
				sbyte airborne_ticks; // bipeds 0x501
				sbyte slipping_ticks; // bipeds 0x502
				sbyte biped_504;
				short biped_508;
				unsigned short : 16;
				real biped_50C;
				real_vector3d biped_514;
				unsigned long : 32; // unused?
				BYTE biped_4D0;
				BYTE biped_4D1;
				Enums::biped_movement_state movement_state; // bipeds 0x4D2
				unsigned char : 8;
				DWORD biped_4D8;
			}biped;
			struct {													// 0x124
				real_point3d position;
				real_vector3d transitional_velocity;
				real_vector3d angular_velocity;
				byte object_data[sizeof(Objects::s_object_data) - FIELD_OFFSET(Objects::s_object_data, datum_role)];
				real driver_power;
				real gunner_power;
				UNKNOWN_TYPE(long);
				Objects::s_vehicle_data vehicle_data;
			}vehicle;
			s_player_update* next;
		}; static_assert( sizeof(s_player_update) == 0x418 );
		struct s_player_update_history
		{
			long next_update_history_id; // maximum = 64
			s_player_update* updates;
			unsigned long : 32;
			long number_of_playbacks;
			long total_ticks;
			long total_updates;
			unsigned long : 32; // 0x18
			unsigned long : 32; // 0x1C
			unsigned long : 32; // 0x20
			real avg_prediction_error;
			real avg_ticks_played_back;
		}; static_assert( sizeof(s_player_update_history) == 0x2C );
	};
};
