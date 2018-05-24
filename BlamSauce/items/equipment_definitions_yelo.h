#pragma once

#include <precompile.h>

namespace Yelo {
	namespace Enums {
		enum equipment_yelo_type : short {
			_equipment_yelo_type_none,

			_equipment_yelo_type_armor_ability,
			_equipment_yelo_type_deployable,

			_equipment_yelo_type
		};

		enum equipment_yelo_function_mode : short {
			_equipment_yelo_function_mode_none,
			_equipment_yelo_function_mode
		};
	};

	namespace Flags {
		enum equipment_yelo_flags : unsigned short { };
	};

	namespace TagGroups {
		struct s_equipment_yelo_armor_ability {
			struct s_tank {
				real size;
				real recharge_rate;
				short count;
				short swap_time;
			} energy_tank;

			struct s_energy {
				real use_rate;
				real recharge_rate;
				real recharge_delay;
			} energy;
		};
		struct s_equipment_yelo_deployable {
			short usage_count;
			unsigned short : 16;
		};

		struct s_equipment_yelo_definition {
			enum { k_max_definition_size = sizeof(tag_reference) * 9 }; // size of the useless padding in equipment

			Flags::equipment_yelo_flags flags;
			unsigned short : 16;
			unsigned long  : 32;
			unsigned long  : 32;
			unsigned long  : 32;

			struct s_effects {
				tag_reference activate;
				tag_reference active;
				tag_reference deactivate;
			}              effects;

		}; static_assert(sizeof(s_equipment_yelo_definition) <= s_equipment_yelo_definition::k_max_definition_size);
	};
};
