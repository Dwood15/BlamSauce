#pragma once

#include <precompile.h>
#include "item_definitions.h"

namespace Yelo
{
	namespace Enums
	{
		enum equipment_powerup : short
		{
			_equipment_powerup_none,

			_equipment_powerup_double_shield,
			_equipment_powerup_over_shield,
			_equipment_powerup_active_camo,
			_equipment_powerup_full_spectrum_vision,

			_equipment_powerup_health,
			_equipment_powerup_grenade,

			_equipment_powerup
		};
	};

	namespace TagGroups
	{
		struct _equipment_definition
		{
			Enums::equipment_powerup powerup_type;
			Enums::grenade_type grenade_type;
			real powerup_time;
			tag_reference pickup_sound;
			union {
				byte p0[sizeof(byte) * (s_equipment_yelo_definition::k_max_definition_size)];
				//s_equipment_yelo_definition yelo;
			};
		}; static_assert( sizeof(_equipment_definition) == 0xA8 );
		struct s_equipment_definition : s_item_definition
		{
			enum { k_group_tag = 'eqip' };

			_equipment_definition equipment;
		};
	};
};
