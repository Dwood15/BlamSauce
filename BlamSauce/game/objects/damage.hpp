/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

#include "../../cseries/base.h"
#include "../../memory/datum_index.h"
#include "../allegiance.h"
#include "../../math/real_math.h"
#include "../../effects/material/material_effect_definitions.hpp"
#include "../../scenario/structures.h"
#include "../../effects/damage/damage_effect_definitions.hpp"
#include "../../models/collision/model_definitions.hpp"

namespace Yelo {
	namespace Flags {
		enum object_damage_flags {
			_object_damage_flag_body_depleted      = 1 << 0,
			_object_damage_flag_destroyed_a_region = 1 << 1,
			_object_damage_flag_destroyed_object   = 1 << 2,
			_object_damage_flag_shield_depleted    = 1 << 3,
			_object_damage_flag_is_enemy_team      = 1 << 4,
			_object_damage_flag_unknown5           = 1 << 5,
			_object_damage_flag_unknown6           = 1 << 6,
			_object_damage_flag_unknown7           = 1 << 7,

			_object_damage_flags
		};

		enum damage_data_flags : short {
			// Incomplete
				_damage_data_flags_affect_target_only_bit,

			_damage_data_flags
		};
	};

	namespace Objects {
		struct s_damage_data {
			datum_index      effect_definition_index;         // 0x0
			long_flags       flags;                        // 0x4
			datum_index      responsible_player_index;         // 0x8
			datum_index      responsible_unit_index;            // 0xC
			Enums::game_team responsible_units_team;      // 0x10
			unsigned short : 16;                                 // 0x12
			Yelo::Scenario::s_scenario_location location;               // 0x14
			real_point3d                        damage_position;               // 0x1C
			UNKNOWN_TYPE(real_vector3d); // position		// 0x28
			UNKNOWN_TYPE(real_vector3d); // direction?		// 0x34
			// scale examples:
			// AOE distance scale (via radius)
			// unit blip type (medium=.5, small=.25, large=1)
			real scale;                              // 0x40
			real damage_multiplier;                     // 0x44
			UNKNOWN_TYPE(real);                        // 0x48 shield or body amount prior to the damage was applied
			Enums::material_type material;               // 0x4C
			unsigned short : 16;                                 // 0x4E
			UNKNOWN_TYPE(long); // only seen this written to, and when it was it was set to a s_projectile_material_response_definition*
		}; static_assert(sizeof(s_damage_data) == 0x54);
	};

	namespace blam {
		using namespace Yelo::Objects;

		inline __cdecl void damage_data_new(s_damage_data &data, datum_index damage_effect_definiton_index) {
			memset(&data, 0, sizeof(data));
			data.effect_definition_index  = damage_effect_definiton_index;
			data.material                 = Enums::_material_type_none;
			data.responsible_player_index = datum_index::null();
			data.responsible_unit_index   = datum_index::null();
			data.responsible_units_team   = Enums::_game_team_none;
			data.location.cluster_index   = NONE;
			data.scale                    = 1.0f;
			data.damage_multiplier        = 1.0f;
		}

		bool __cdecl object_restore_body(datum_index object_index);

		void __cdecl object_deplete_body(datum_index object_index);

		void __cdecl object_deplete_shield(datum_index object_index);

		void __cdecl object_double_charge_shield(datum_index object_index);

		void __cdecl area_of_effect_cause_damage(s_damage_data &data, datum_index unused_object_index = datum_index::null());

		void __cdecl object_cause_damage(s_damage_data &data, datum_index damaged_object_index,
													short node_index = NONE, short region_index = NONE, short damage_materials_element_index = NONE,
													real_vector3d *normal = NULL);
	};
};


namespace Yelo::Objects
{

	static void __cdecl object_damage_object_body_hook(datum_index object_index,
																		long region_index, long node_index, void* /*unknown*/,
																		const Yelo::TagGroups::s_damage_resistance* damage_resistance, const TagGroups::collision_model_material* damage_material,
																		const TagGroups::s_damage_definition* damage_definition, Objects::s_damage_data* damage_data,
																		void*, __out real&, __out real&, real, bool)
	{
		//////////////////////////////////////////////////////////////////////////
		// Does this map have any extensions defined at all?
		const TAG_TBLOCK(& damage_extensions, TagGroups::s_object_damage_extension) = Yelo::TagGroups::_global_yelo_globals->object_damage_extensions;
		if(damage_extensions.Count == 0)
			return;

		s_object_header_datum* object_header_datums = *Objects::ObjectHeader();
		s_object_data* object_data = object_header_datums[object_index.index]._object;


		//////////////////////////////////////////////////////////////////////////
		// Lookup the current object's definition in the damge_extensions block
		const datum_index* object_definition_index = object_data->GetTagDefinition();

		const TagGroups::s_object_damage_extension* dmg_ext = nullptr;
		for(long x = 0; x < damage_extensions.Count; x++)
		{
			const TagGroups::s_object_damage_extension* def = &damage_extensions[x];

			if(def->object.tag_index == *object_definition_index)
				dmg_ext = def;
		}

		//////////////////////////////////////////////////////////////////////////
		// If we found a definition, then the map has extensions defined for this object type
		// TODO: ChokingVictim's code is...choking me up. What he provided isn't making sense, holding off on the integration for this for the time being.
		if(dmg_ext != nullptr)
		{
			real max_vitality = *object_data->GetMaximumVitality();
			long region_vitality = (*object_data->GetRegionVitality()) + region_index;
			real current_region_damage = CAST(real, region_vitality) / max_vitality;

			long region_count = dmg_ext->regions.Count;
			const TagGroups::s_object_damage_region_extension& region_ext = dmg_ext->regions[region_index];

			// If the objects region count is greater than [k_maximum_regions_per_model], accommodate for its place in the region vitality/permutation array
			// Else [k_maximum_regions_per_model] is the max array element in the region vitality/permutation array
			byte* region_perm = object_data->GetRegionVitality() +
									  (region_count >= Enums::k_maximum_regions_per_model ? region_count : Enums::k_maximum_regions_per_model) +
									  region_index;

			// loop through the object permutations and test the region's damage
			for(long x = *region_perm + 1; x < region_ext.permutations.Count; x++) {
				real current_region_damage_threshold = region_ext.permutations[x].damage_threshold;

				// if the current damage taken by this region is greater than or equal to the damage threshold, switch perms
				if (current_region_damage_threshold > 0.0f && current_region_damage >= current_region_damage_threshold) {
					*region_perm = CAST(byte, x);
				}
			}
		}
	}

	static void DamageInitialize()
	{
		Memory::WriteRelativeJmp(&object_damage_object_body_hook, GET_FUNC_VPTR(OBJECT_DAMAGE_OBJECT_BODY_HOOK), true);
	}

	static void DamageDispose()
	{
	}

};
