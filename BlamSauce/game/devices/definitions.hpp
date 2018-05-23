#pragma once
#include <precompile.h>
#include "../objects/object_definitions.hpp"

namespace Yelo
{
	namespace TagGroups
	{
		struct _device_definition
		{
			struct _flags {
				unsigned long position_loops_bit:1;
				unsigned long position_not_interpolated_bit:1;
			}flags;

			struct _timing {
				real transition_time;
				real acceleration_time;
			}power_time, position_time, depower_time;

			short function_exports[Enums::k_number_of_incoming_object_functions]; // Enums::device_function_mode

			tag_reference open; // 'snd!', 'effe');
			tag_reference close; //'snd!', 'effe');

			tag_reference opened;
			tag_reference closed;

			tag_reference depowered;
			tag_reference repowered;

			real delay_time;
			real:8 * sizeof(real) * 2; // 8

			tag_reference delay_effect;
			real automatic_activation_radius;
			long:8 * sizeof(long) * 21;

			struct { // if([tag values] != 0) then * 30.0f, then 1.0f / result
				struct {
					real transition_time;
					real acceleration_time;
				}power_time, position_time, depower_time;

				real delay_time;
			}runtime;
		}; static_assert( sizeof(_device_definition) == 0x114 );

		//////////////////////////////////////////////////////////////////////////

		struct _control_definition
		{
			control_type type;
			control_trigger triggers_when;
			real call_value;
			long:8 * sizeof(long) * 20; // 80

			tag_reference on;
			tag_reference off;
			tag_reference deny;
		}; static_assert( sizeof(_control_definition) == 0x88 );

		//////////////////////////////////////////////////////////////////////////

		struct _machine_definition
		{
			machine_type type;
			struct _Flags {
				unsigned short pathfinding_obstacle_bit:1;
				unsigned short but_not_when_open_bit:1;
				unsigned short elevator_bit:1;
			}flags;
			real door_open_time;
			long:8 * sizeof(long) * 20; // 80

			machine_collision_response collision_response;
			short elevator_node;
			long:8 * sizeof(long) * 13; // 52

			long runtime_door_open_time; // door_open_time * 30.0f
		}; static_assert( sizeof(_machine_definition) == 0x94 );

		//////////////////////////////////////////////////////////////////////////


		struct s_device_definition : s_object_definition
		{
			enum { k_group_tag = 'devi' };

			_device_definition device;
		};

		struct s_control_definition : s_device_definition
		{
			enum { k_group_tag = 'ctrl' };

			_control_definition control;
		};

		struct s_machine_definition : s_device_definition
		{
			enum { k_group_tag = 'mach' };

			_machine_definition machine;
		};
	};
};
