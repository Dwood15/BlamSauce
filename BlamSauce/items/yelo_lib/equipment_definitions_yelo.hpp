/*
	Yelo: Open Sauce SDK

	See license\OpenSauce\OpenSauce for specific license information
*/
#pragma once

#include <YeloLib/tag_files/tag_groups_base_yelo.hpp>

namespace Yelo
{
	namespace Enums
	{
		enum equipment_yelo_type : short
		{
			_equipment_yelo_type_none,

			_equipment_yelo_type_armor_ability,
			_equipment_yelo_type_deployable,

			_equipment_yelo_type,
		};

		enum equipment_yelo_function_mode : short
		{
			_equipment_yelo_function_mode_none,

			_equipment_yelo_function_mode,
		};
	};

	namespace Flags
	{
		enum equipment_yelo_flags : unsigned short
		{
		};
	};

	namespace TagGroups
	{
		struct s_equipment_yelo_armor_ability
		{
			struct s_tank {
				TAG_FIELD(real, size);
				TAG_FIELD(real, recharge_rate);
				TAG_FIELD(short, count);
				TAG_FIELD(short, swap_time);
			}energy_tank;

			struct s_energy {
				TAG_FIELD(real, use_rate);
				TAG_FIELD(real, recharge_rate);
				TAG_FIELD(real, recharge_delay);
			}energy;
		};
		struct s_equipment_yelo_deployable
		{
			TAG_FIELD(short, usage_count);
			unsigned short : 16;
		};

		struct s_equipment_yelo_definition
		{
			enum { k_max_definition_size = sizeof(tag_reference)*9 }; // size of the useless padding in equipment

			TAG_FIELD(Flags::equipment_yelo_flags, flags);
			unsigned short : 16;
			unsigned long : 32;
			unsigned long : 32;
			unsigned long : 32;

			struct s_effects {
				TAG_FIELD(tag_reference, activate, 'effe', 'snd!');
				TAG_FIELD(tag_reference, active, 'effe', 'snd!');
				TAG_FIELD(tag_reference, deactivate, 'effe', 'snd!');
			}effects;

		}; static_assert( sizeof(s_equipment_yelo_definition) <= s_equipment_yelo_definition::k_max_definition_size );
	};
};
