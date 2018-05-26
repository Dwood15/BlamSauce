#pragma once

#include <precompile.h>
#include "field_definitions.h"

namespace Yelo::Objects {
	static s_object_field_definition g_object_real_fields[] = {
		{"function_out",          std::size("function_out") - 1,          Enums::_hs_type_real, Enums::_object_field_real_function_out,            false, true},
		{"radius",                std::size("radius") - 1,                Enums::_hs_type_real, Enums::_object_field_real_radius,                  false, true},
		{"scale",                 std::size("scale") - 1,                 Enums::_hs_type_real, Enums::_object_field_real_scale,                   false, true},
		{
		 "maximum_vitality",      std::size("maximum_vitality") - 1,      Enums::_hs_type_real, Enums::_object_field_real_maximum_vitality,        false
		}, // Keep for backwards compatibility ONLY, value is incorrect
		{
		 "current_vitality",      std::size("current_vitality") - 1,      Enums::_hs_type_real, Enums::_object_field_real_current_vitality,        false
		}, // Keep for backwards compatibility ONLY, value is incorrect
		{"maximum_health",        std::size("maximum_health") - 1,        Enums::_hs_type_real, Enums::_object_field_real_maximum_health,          false},
		{"maximum_shield",        std::size("maximum_shield") - 1,        Enums::_hs_type_real, Enums::_object_field_real_maximum_shield,          false},
		{"current_health",        std::size("current_health") - 1,        Enums::_hs_type_real, Enums::_object_field_real_current_health,          false},
		{"current_shield",        std::size("current_shield") - 1,        Enums::_hs_type_real, Enums::_object_field_real_current_shield,          false},

		{"position",              std::size("position") - 1,              Enums::_hs_type_real, Enums::_object_field_vector_position,              true},
		{"transitional_velocity", std::size("transitional_velocity") - 1, Enums::_hs_type_real, Enums::_object_field_vector_transitional_velocity, true},
		{"forward",               std::size("forward") - 1,               Enums::_hs_type_real, Enums::_object_field_vector_forward,               true},
		{"up",                    std::size("up") - 1,                    Enums::_hs_type_real, Enums::_object_field_vector_up,                    true},
		{"angular_velocity",      std::size("angular_velocity") - 1,      Enums::_hs_type_real, Enums::_object_field_vector_angular_velocity,      true},
		{"center",                std::size("center") - 1,                Enums::_hs_type_real, Enums::_object_field_vector_center,                false, true},

		{"desired_facing",        std::size("desired_facing") - 1,        Enums::_hs_type_real, Enums::_unit_field_vector_desired_facing,          true},
		{"desired_aiming",        std::size("desired_aiming") - 1,        Enums::_hs_type_real, Enums::_unit_field_vector_desired_aiming,},
		{"aiming",                std::size("aiming") - 1,                Enums::_hs_type_real, Enums::_unit_field_vector_aiming,},
		{"aiming_velocity",       std::size("aiming_velocity") - 1,       Enums::_hs_type_real, Enums::_unit_field_vector_aiming_velocity,},
		{"looking",               std::size("looking") - 1,               Enums::_hs_type_real, Enums::_unit_field_vector_looking,},
		{"looking_angles",        std::size("looking_angles") - 1,        Enums::_hs_type_real, Enums::_unit_field_vector_looking_angles,},
		{"looking_velocity",      std::size("looking_velocity") - 1,      Enums::_hs_type_real, Enums::_unit_field_vector_looking_velocity,},
	};

	static s_object_field_definition g_weapon_real_fields[] = {
		{"heat",        std::size("heat") - 1,        Enums::_hs_type_real, Enums::_weapon_field_real_heat,},
		{"age",         std::size("age") - 1,         Enums::_hs_type_real, Enums::_weapon_field_real_age, true},
		{"light_power", std::size("light_power") - 1, Enums::_hs_type_real, Enums::_weapon_field_real_light_power,},
	};

	static s_object_field_definition g_weapon_integer_magazine_fields[] = {
		{"state",  std::size("state") - 1,  Enums::_hs_type_short, Enums::_weapon_field_integer_magazine_state, false, true}, // READONLY
		{"reload", std::size("reload") - 1, Enums::_hs_type_short, Enums::_weapon_field_integer_magazine_reload,},
		{"rounds", std::size("rounds") - 1, Enums::_hs_type_short, Enums::_weapon_field_integer_magazine_rounds,},
	};

	static s_object_field_definition g_weapon_tag_real_trigger_fields[] = {
		{"spew_time",         std::size("spew_time") - 1,         Enums::_hs_type_real, Enums::_weapon_tag_field_real_trigger_spew_time,},
		{"rounds_per_second", std::size("rounds_per_second") - 1, Enums::_hs_type_real, Enums::_weapon_tag_field_real_trigger_rounds_per_second,},
	};

	static s_object_field_definition g_unit_object_index_fields[] = {
		{"throwing_grenade_projectile",      std::size("throwing_grenade_projectile") - 1,      Enums::_hs_type_object, Enums::_unit_field_object_index_throwing_grenade_projectile,      false, true},
		{
		 "weapon",                           std::size("weapon") -
														 1,                                                 Enums::_hs_type_weapon, Enums::_unit_field_object_index_weapon,                           true,  true, true
		},
		// TODO: when we add network support for equipment, update this field entry's flags
		{"equipment",                        std::size("equipment") - 1,                        Enums::_hs_type_object, Enums::_unit_field_object_index_equipment,                        false, true},
		//FIELD_ENTRY( unit, unit,		object_index, 40C,										false, true),
		{"damage_responsible_flamer_object", std::size("damage_responsible_flamer_object") - 1, Enums::_hs_type_object, Enums::_unit_field_object_index_damage_responsible_flamer_object, false, true},
		{
		 "recent_damage.unit",               std::size("recent_damage.unit") -
														 1,                                                 Enums::_hs_type_unit, Enums::_unit_field_object_index_recent_damage_unit,                  false, true, true
		},
	};

	// We use bool for byte-size fields as hs_type doesn't have an 8-bit integer
	static s_object_field_definition g_unit_integer_fields[] = {
		{"ticks_until_flame_to_death",   std::size("ticks_until_flame_to_death") - 1,   Enums::_hs_type_byte,  Enums::_unit_field_integer_ticks_until_flame_to_death, false, true},
		{"throwing_grenade_state",       std::size("throwing_grenade_state") - 1,       Enums::_hs_type_byte,  Enums::_unit_field_integer_throwing_grenade_state,     false, true},

		{"total_grenade_count[frag]",    std::size("total_grenade_count[frag]") - 1,    Enums::_hs_type_byte, Enums::_unit_field_integer_total_grenade_count_frag,     true},
		{"total_grenade_count[plasma]",  std::size("total_grenade_count[plasma]") - 1,  Enums::_hs_type_byte, Enums::_unit_field_integer_total_grenade_count_plasma,   true},
		{"total_grenade_count[custom2]", std::size("total_grenade_count[custom2]") - 1, Enums::_hs_type_byte, Enums::_unit_field_integer_total_grenade_count_custom2,  true},
		{"total_grenade_count[custom3]", std::size("total_grenade_count[custom3]") - 1, Enums::_hs_type_byte, Enums::_unit_field_integer_total_grenade_count_custom3,  true},

		{"current_grenade_index",        std::size("current_grenade_index") - 1,        Enums::_hs_type_byte,  Enums::_unit_field_integer_current_grenade_index,      false, true},
		{"zoom_level",                   std::size("zoom_level") - 1,                   Enums::_hs_type_byte,  Enums::_unit_field_integer_zoom_level,                 false, true},
		{"desired_zoom_level",           std::size("desired_zoom_level") - 1,           Enums::_hs_type_byte,  Enums::_unit_field_integer_desired_zoom_level,         true},

		{"vehicle_seat_index",           std::size("vehicle_seat_index") - 1,           Enums::_hs_type_short, Enums::_unit_field_integer_vehicle_seat_index,         false, true},
		{"current_weapon_index",         std::size("current_weapon_index") - 1,         Enums::_hs_type_short, Enums::_unit_field_integer_current_weapon_index,       true,  true},
		{"feign_death_timer",            std::size("feign_death_timer") - 1,            Enums::_hs_type_short, Enums::_unit_field_integer_feign_death_timer,          false, true},
		{"killing_spree_count",          std::size("killing_spree_count") - 1,          Enums::_hs_type_short, Enums::_unit_field_integer_killing_spree_count,        false, true},
	};

	static s_object_field_definition g_unit_real_fields[] = {
		{"driver_power",                         std::size("driver_power") - 1,                         Enums::_hs_type_real, Enums::_unit_field_real_driver_power,},
		{"gunner_power",                         std::size("gunner_power") - 1,                         Enums::_hs_type_real, Enums::_unit_field_real_gunner_power,},
		{"integrated_light_power",               std::size("integrated_light_power") - 1,               Enums::_hs_type_real, Enums::_unit_field_real_integrated_light_power,},
		{"integrated_light_toggle_power",        std::size("integrated_light_toggle_power") - 1,        Enums::_hs_type_real, Enums::_unit_field_real_integrated_light_toggle_power,},
		{"integrated_night_vision_toggle_power", std::size("integrated_night_vision_toggle_power") - 1, Enums::_hs_type_real, Enums::_unit_field_real_integrated_night_vision_toggle_power,},
		{"camo_power",                           std::size("camo_power") - 1,                           Enums::_hs_type_real, Enums::_unit_field_real_camo_power,},
		{"full_spectrum_vision_power",           std::size("full_spectrum_vision_power") - 1,           Enums::_hs_type_real, Enums::_unit_field_real_full_spectrum_vision_power,},
	};
};
#undef FIELD_INDEX_NAME
#undef FIELD_ENTRY
#undef FIELD_ENTRY2
