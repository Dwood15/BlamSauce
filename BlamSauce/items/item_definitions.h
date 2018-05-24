#pragma once
#include <precompile.h>

#include "../tags/group/markup.h"
#include "../cseries/base.h"
#include "../game/objects/object_definitions.hpp"

namespace Yelo::TagGroups
	{
		struct _item_definition
		{
			struct _item_definition_flags {
				unsigned long maintains_z_up_bit:1;
				unsigned long destroyed_by_explosions_bit:1;
				unsigned long unaffected_by_gravity_bit:1;
			} flags;

			static_assert( sizeof(_item_definition_flags) == sizeof(unsigned long) );

			short message_index;
			short sort_order;
			real scale;
			short hud_message_value_scale;
			unsigned short : 16;

			long:8 * sizeof(long) * 4;
			short function_exports[Enums::k_number_of_incoming_object_functions];
			long:8 * sizeof(long) * 41;

			struct {
				tag_reference material_effects;
				tag_reference collision_sound;
			} references;

			long:8 * sizeof(long) * 30;

			struct {
				real_bounds delay;
				tag_reference detonating_effect;
				tag_reference effect;
			} detonation;
		}; static_assert( sizeof(_item_definition) == 0x18C );


		struct s_item_definition : s_object_definition
		{
			_item_definition item;
		}; static_assert( sizeof(s_item_definition) == 0x308 );
	};
